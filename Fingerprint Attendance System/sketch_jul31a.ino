#include <Adafruit_Fingerprint.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>
#include <EEPROM.h>
#include <time.h>
#include "esp_wpa2.h"  // Deprecated but used as per your setup

// WiFi Credentials
const char* ssid = "IIITB-Milan";
const char* identity = "comet.lab5@iiitb.ac.in";
const char* username = "iiitb\\comet.lab5";
const char* password = "Welcome@2023";

// Google Sheets Web App URL (Replace with your actual deployed URL)
const char* WEB_APP_URL = "https://script.google.com/macros/s/AKfycbyQLuZsRaztI69OqJyXtPTOVHk7aI-ZRZoElGLQPEUBBM9oDVVuU2GMJgBBBMibMuNoZQ/exec";

// Fingerprint sensor serial & instance
HardwareSerial mySerial(2);  // RX = GPIO16, TX = GPIO17
Adafruit_Fingerprint finger(&mySerial);

#define BUZZER_PIN 4

#define MAX_USERS 128
#define NAME_LEN 20
#define ID_LEN 20
#define EEPROM_SIZE (MAX_USERS * (NAME_LEN + ID_LEN))
#define SERIAL_SIZE sizeof(unsigned long)

String userNames[MAX_USERS];
String cometIDs[MAX_USERS];

int fingerIdToUserIndex[129]; // 1-based finger IDs mapping

#define SERIAL_ADDR EEPROM_SIZE
unsigned long attendanceSerial = 1;

// ---------------- Buzzer functions -------------------
// Simple buzz twice (tones with pause)
void buzz() {
  tone(BUZZER_PIN, 1000, 200);
  delay(300);
  tone(BUZZER_PIN, 1000, 200);
}
// Buzz pattern for HTTP 302 response
void buzzOn302() {
  tone(BUZZER_PIN, 1000, 500);
  delay(500);
  tone(BUZZER_PIN, 1000, 500);
}
// -----------------------------------------------------

// Initialize fingerId to user index mapping - adjust this for your setup
void initFingerIdMapping() {
  for (int i = 0; i <= 128; i++) {
    fingerIdToUserIndex[i] = -1;
  }
  fingerIdToUserIndex[1] = 15; // Example: finger ID 1 maps to user index 15
  // Add additional mappings here as needed
  // fingerIdToUserIndex[2] = 7; ...
}

// Load attendance serial number from EEPROM
void loadAttendanceSerial() {
  unsigned long val = 0;
  for (int i = 0; i < SERIAL_SIZE; i++) {
    val |= ((unsigned long)EEPROM.read(SERIAL_ADDR + i)) << (8 * i);
  }
  if (val == 0xFFFFFFFF || val == 0) {
    attendanceSerial = 1;
  } else {
    attendanceSerial = val;
  }
  Serial.print("Loaded attendanceSerial: ");
  Serial.println(attendanceSerial);
}

// Save attendance serial number to EEPROM
void saveAttendanceSerial() {
  for (int i = 0; i < SERIAL_SIZE; i++) {
    EEPROM.write(SERIAL_ADDR + i, (attendanceSerial >> (8 * i)) & 0xFF);
  }
  EEPROM.commit();
  Serial.print("Saved attendanceSerial = ");
  Serial.println(attendanceSerial);
}

// Load stored user data (names and comet IDs) from EEPROM
void loadUserData() {
  for (int id = 0; id < MAX_USERS; id++) {
    int base = id * (NAME_LEN + ID_LEN);
    char nameArray[NAME_LEN + 1] = {0};
    char cometArray[ID_LEN + 1] = {0};

    for (int i = 0; i < NAME_LEN; i++) {
      nameArray[i] = EEPROM.read(base + i);
    }
    for (int i = 0; i < ID_LEN; i++) {
      cometArray[i] = EEPROM.read(base + NAME_LEN + i);
    }

    String name = String(nameArray);
    String comet = String(cometArray);

    name.trim();
    comet.trim();

    if (name.length() > 0 && comet.length() > 0) {
      userNames[id] = name;
      cometIDs[id] = comet;
    } else {
      userNames[id] = "";
      cometIDs[id] = "";
    }
  }
}

// Save user data (name and comet ID) for a particular id into EEPROM
void saveUserData(int id) {
  int base = id * (NAME_LEN + ID_LEN);
  for (int i = 0; i < NAME_LEN; i++) {
    EEPROM.write(base + i, (i < userNames[id].length()) ? userNames[id][i] : 0);
  }
  for (int i = 0; i < ID_LEN; i++) {
    EEPROM.write(base + NAME_LEN + i, (i < cometIDs[id].length()) ? cometIDs[id][i] : 0);
  }
  EEPROM.commit();
}

// Connect ESP32 to WPA2 Enterprise WiFi
void connectToWiFi() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);

  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)identity, strlen(identity));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
  esp_wifi_sta_wpa2_ent_enable();

  Serial.print("Connecting to WPA2-Enterprise WiFi");
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi.");
  }
}

// Get fingerprint ID or -1 if no fingerprint matched
int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerSearch();
  if (p != FINGERPRINT_OK) return -1;

  Serial.print("Matched fingerprint ID: ");
  Serial.println(finger.fingerID);
  return finger.fingerID;
}

// Send attendance data to Google Sheets (without serial number field)
void sendToGoogleSheet(unsigned long serial, String name, String cometID) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(WEB_APP_URL);
    http.addHeader("Content-Type", "application/json");

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("❌ Failed to get time from NTP!");
      return;
    }

    char timeStr[25];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);

    // JSON without serial field as requested
    String json = "{";
    json += "\"name\":\"" + name + "\",";
    json += "\"id\":\"" + cometID + "\",";
    json += "\"time\":\"" + String(timeStr) + "\"";
    json += "}";

    Serial.println("Sending to Google Sheets:");
    Serial.println(json);

    int response = http.POST(json);
    Serial.print("Google Sheets response code: ");
    Serial.println(response);

    if (response == 302) {
      Serial.println("Received HTTP 302 - buzzing buzzer.");
      buzzOn302();
    }

    if (response <= 0) {
      Serial.print("HTTP error: ");
      Serial.println(http.errorToString(response));
    } else if (response != 302) {
      String payload = http.getString();
      Serial.print("Server response: ");
      Serial.println(payload);
    }

    http.end();
  } else {
    Serial.println("❌ WiFi not connected during sendToGoogleSheet!");
  }
}

// Enroll user with fingerprint and store user info in EEPROM
void enrollUser() {
  Serial.println("Enter ID to enroll (1–127): ");
  String idStr = "";
  while (idStr.length() == 0) {
    if (Serial.available()) {
      idStr = Serial.readStringUntil('\n');
      idStr.trim();
    }
  }
  int id = idStr.toInt();
  if (id < 1 || id >= MAX_USERS) {
    Serial.println("Invalid ID. Must be between 1 and 127.");
    return;
  }

  Serial.println("Enter Name: ");
  String name = "";
  while (name.length() == 0) {
    if (Serial.available()) {
      name = Serial.readStringUntil('\n');
      name.trim();
    }
  }

  Serial.println("Enter Comet ID: ");
  String cometID = "";
  while (cometID.length() == 0) {
    if (Serial.available()) {
      cometID = Serial.readStringUntil('\n');
      cometID.trim();
    }
  }

  Serial.println("Place finger on sensor...");
  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    Serial.println("Error capturing image.");
    return;
  }

  Serial.println("Remove finger...");
  delay(2000);
  while (finger.getImage() != FINGERPRINT_NOFINGER);

  Serial.println("Place same finger again...");
  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    Serial.println("Error capturing second image.");
    return;
  }

  p = finger.createModel();
  if (p != FINGERPRINT_OK) {
    Serial.println("Could not create fingerprint model.");
    return;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Fingerprint enrolled successfully!");

    userNames[id] = name;
    cometIDs[id] = cometID;
    saveUserData(id);

    fingerIdToUserIndex[id] = id; // Map sensor finger ID to user index
  } else {
    Serial.println("Failed to store fingerprint.");
  }
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  EEPROM.begin(EEPROM_SIZE + SERIAL_SIZE);

  loadUserData();
  loadAttendanceSerial();
  initFingerIdMapping();

  connectToWiFi();

  // Configure NTP time (IST offset 19800 seconds)
  configTime(19800, 0, "pool.ntp.org", "time.nist.gov");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor detected.");
  } else {
    Serial.println("Fingerprint sensor NOT found. Check connections!");
    while (1) delay(1);
  }

  Serial.println("System ready.");
  Serial.println("Commands: P = print users, E = enroll user, C = clear all data");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'P') {
      Serial.println();
      Serial.println("Printing all saved users:");
      loadUserData();
      printAllUserData();
      Serial.println();
    } else if (cmd == 'E') {
      Serial.println();
      Serial.println("Enroll user command selected.");
      enrollUser();
      Serial.println();
    } else if (cmd == 'C') {
      Serial.println();
      Serial.println("Clear all data command selected.");
      clearAllData();
      Serial.println();
    }
  }

  int fingerId = getFingerprintID();
  if (fingerId != -1 && fingerId <= 128) {
    int userIndex = fingerIdToUserIndex[fingerId];
    if (userIndex != -1 && userIndex < MAX_USERS) {
      String name = userNames[userIndex];
      String cometID = cometIDs[userIndex];

      if (name != "" && cometID != "") {
        buzz();
        sendToGoogleSheet(attendanceSerial, name, cometID);
        attendanceSerial++;
        saveAttendanceSerial();
      }
    } else {
      Serial.println("Fingerprint matched but not mapped to a user.");
    }
  }

  delay(1000);
}

// Clear all EEPROM user data and reset attendance serial
void clearAllData() {
  Serial.println("Clearing all EEPROM user data and resetting attendance serial");

  for (int i = 0; i < EEPROM_SIZE + SERIAL_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();

  for (int i = 0; i < MAX_USERS; i++) {
    userNames[i] = "";
    cometIDs[i] = "";
  }

  attendanceSerial = 1;
  saveAttendanceSerial();

  Serial.println("All data cleared and attendance serial reset to 1.");
}

// Print all stored user info on Serial
void printAllUserData() {
  Serial.println("------ EEPROM User Data ------");
  bool anyFound = false;
  for (int id = 0; id < MAX_USERS; id++) {
    if (userNames[id].length() > 0 && cometIDs[id].length() > 0) {
      Serial.print("ID: ");
      Serial.print(id);
      Serial.print(" | Name: ");
      Serial.print(userNames[id]);
      Serial.print(" | CometID: ");
      Serial.println(cometIDs[id]);
      anyFound = true;
    }
  }
  if (!anyFound) {
    Serial.println("[No user data found in EEPROM]");
  }
  Serial.println("------------------------------");
}
