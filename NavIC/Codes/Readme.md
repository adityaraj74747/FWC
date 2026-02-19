NAVIC L5 SDR RECEIVER PROJECT

This project was carried out under the guidance of Mr. Srikanth Reddy, Training Specialist, IIITB. The objective of this work is to implement a real-time NavIC L5 receiver using Software Defined Radio (SDR).

PROJECT OVERVIEW

A real-time NavIC L5 signal transmission and reception chain is implemented using SDR hardware. Signal generation, transmission, reception, and position computation are carried out using open-source tools and custom implementations.

REQUIREMENTS

Hardware Requirements:
USRP SDR
bladeRF SDR
PC with 64-bit Linux operating system

Software Requirements:
RTKLIB
UHD (USRP Hardware Driver)

SYSTEM SPECIFICATIONS

Receiver sampling frequency: 2.048 MHz

INSTALLATIONS

Install and configure bladeRF and USRP using the instructions provided in the following link:
https://github.com/adityaraj74747/FWC/blob/main/NavIC/Codes/installations.txt

TRANSMITTER SETUP

To generate NavIC L5 IQ samples, download the transmitter source code using SVN:

svn co https://github.com/adityaraj74747/FWC/blob/main/NavIC/Codes/Transmitter

Compile the transmitter:

make

This generates a binary file containing IQ samples for a duration of 300 seconds with 16-bit resolution. In the generated binary file, the first 16 bits correspond to the I component and the next 16 bits correspond to the Q component. This pattern continues throughout the file and is used for SDR transmission.

Generate IQ samples using navic-sdr-sim:

./navic-sdr-sim -e brdc1380.23n -s 2048000 -l 30,120,100

For SDR transmission that requires 8-bit IQ samples, generate the file with 8-bit resolution. In this format, the first 8 bits correspond to I and the next 8 bits correspond to Q:

./navic-sdr-sim -e brdc1380.23n -s 2048000 -l 30,120,100 -b 8

RECEIVER SETUP

To run the NavIC receiver, download the receiver source code:

svn co https://github.com/adityaraj74747/FWC/blob/main/NavIC/Codes/Receiver

Navigate to the Linux CLI directory:

cd Receiver/cli/linux

Compile the receiver:

make

Move to the binary directory:

cd Receiver/bin

Launch the SDR receiver application:

./ignss-sdrcli

RTKLIB INSTALLATION AND POSITION COMPUTATION

Clone the RTKLIB repository:

git clone https://github.com/tomojitakasu/RTKLIB.git

Navigate to the rnx2rtkp build directory:

cd RTKLIB/app/rnx2rtkp/gcc

Compile RTKLIB:

make

Copy the generated rnx2rtkp executable to the directory containing the generated RINEX observation and navigation files. Execute RTKLIB using the following command:

./rnx2rtkp -p 2 -f 1 -t -s , -l 0.0 0.0 0.0 ignss-sdrlib.obs ignss-sdrlib.nav
