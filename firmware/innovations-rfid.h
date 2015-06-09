/*
* FILE:        innovations-rfid.h
* VERSION:     0.1
* PURPOSE:     Particle Core lib for Innovations ID-2/ID-12/ID-20 RFID reader sensors
* LICENSE:     GPL v3 (http://www.gnu.org/licenses/gpl.html)
*
* Based on "Can You ID This? ID-20 RFID Reader + Arduino" example
* (http://bildr.org/2011/02/rfid-arduino/)
*
* This library supports the Innovations ID-x sensor on the following pins
* VIN, GND, Tx, D6 (this digital input is configurable from setup() function)
*/
#include "application.h"

class InnovationsRFID{
public:
	InnovationsRFID();
	char tag[13];
	void setupRFID(uint8_t resetPin);
	bool readTag();
	void resetReader();
	bool compareTag(char one[], char two[]);
	void clearTag();
private:
	uint8_t RFIDResetPin;
	bool checkTagChecksum(char bytesRead[]);
	byte getASCICode(byte val);
};