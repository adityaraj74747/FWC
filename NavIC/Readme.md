# NAVIC L5 SDR RECEIVER PROJECT

## Overview

This project implements a **real-time NavIC L5 receiver** using **Software Defined Radio (SDR)**. The complete signal chain—from baseband signal generation to RF transmission, reception, and position computation—is realized using open-source tools and custom-developed modules.

The work was carried out under the guidance of **Mr. Srikanth Reddy**, Training Specialist, **IIIT Bangalore (IIITB)**.

---

## Objectives

- Generate NavIC L5 baseband IQ samples  
- Transmit NavIC L5 signals using SDR hardware  
- Receive and process NavIC L5 signals in real time  
- Decode observations and compute receiver position using RTKLIB  

---

## System Architecture

1. Signal Generation – NavIC L5 IQ samples using `navic-sdr-sim`  
2. Transmission – SDR-based RF transmission (USRP / bladeRF)  
3. Reception – Real-time SDR receiver processing  
4. Observation Generation – RINEX observation and navigation files  
5. Position Computation – RTKLIB-based PVT solution  

---

## Requirements

### Hardware Requirements
- USRP SDR  
- bladeRF SDR  
- PC with 64-bit Linux operating system  

### Software Requirements
- UHD (USRP Hardware Driver)  
- bladeRF drivers and utilities  
- RTKLIB  
- SVN, Git, GCC toolchain  

---

## System Specifications

- Receiver Sampling Frequency: **2.048 MHz**  
- Signal Type: **NavIC L5**  
- IQ Format: **16-bit / 8-bit (I/Q interleaved)**  

---

## Installations

Install and configure **USRP** and **bladeRF** using the instructions provided at:

https://github.com/adityaraj74747/FWC/blob/main/NavIC/Codes/installations.txt

Ensure that SDR devices are properly detected before proceeding.

---

## Transmitter Setup

### Download Transmitter Source Code

```bash
svn co https://github.com/adityaraj74747/FWC/blob/main/NavIC/Codes/Transmitter
```

### Compile the Transmitter

```bash
make
```

This generates a binary file containing IQ samples with:
- Duration: 300 seconds  
- Resolution: 16-bit  
- Format:
  - First 16 bits → I  
  - Next 16 bits → Q  
  - Pattern repeats throughout the file  

---

### Generate NavIC L5 IQ Samples Using navic-sdr-sim

#### 16-bit IQ Samples

```bash
./navic-sdr-sim -e brdc0470.26n -s 2048000 -l 30,120,100
```

#### 8-bit IQ Samples (For SDRs requiring 8-bit input)

```bash
./navic-sdr-sim -e brdc0470.26n -s 2048000 -l 30,120,100 -b 8
```

8-bit IQ Format:
- First 8 bits → I  
- Next 8 bits → Q  

---

## Receiver Setup

### Download Receiver Source Code

```bash
svn co https://github.com/adityaraj74747/FWC/blob/main/NavIC/Codes/Receiver
```

### Compile the Receiver

```bash
cd Receiver/cli/linux
make
```

### Run the Receiver

```bash
cd Receiver/bin
./ignss-sdrcli
```

The receiver performs:
- RF signal capture  
- Baseband processing  
- Acquisition and tracking  
- RINEX observation and navigation file generation  

---

## RTKLIB Installation and Position Computation

### Clone RTKLIB

```bash
git clone https://github.com/tomojitakasu/RTKLIB.git
```

### Compile rnx2rtkp

```bash
cd RTKLIB/app/rnx2rtkp/gcc
make
```

### Compute Receiver Position

Copy the `rnx2rtkp` binary to the directory containing the RINEX files and run:

```bash
./rnx2rtkp -p 2 -f 1 -t -s , -l 0.0 0.0 0.0 ignss-sdrlib.obs ignss-sdrlib.nav
```

This computes the receiver position using NavIC RINEX observation and navigation files.

---

## Outputs

- RINEX Observation File (.obs)  
- RINEX Navigation File (.nav)  
- Receiver position (latitude, longitude, height)  
- Quality and accuracy metrics  

---

## Notes

- Ensure correct SDR sampling rate and clock configuration  
- Use appropriate RF gain to avoid saturation  
- Accurate broadcast ephemeris (BRDC file) is essential for correct positioning  

---
