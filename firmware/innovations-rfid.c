/*
* FILE:        innovations-rfid.c
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
#include "Innovations-RFID.h"

#define DEBUG_MODE_RFID

InnovationsRFID::InnovationsRFID(){
	clearTag();
}

void InnovationsRFID::setupRFID(uint8_t resetPin){
	RFIDResetPin = resetPin;

	pinMode(RFIDResetPin, OUTPUT); //RFID Reset
	digitalWrite(RFIDResetPin, HIGH);
	Serial1.begin(9600);
}

bool InnovationsRFID::readTag(){
	char bytesRead[13];
	int index = 0;
	boolean reading = false;
	boolean cardPresent = false;

	while (Serial1.available()){
		cardPresent = true;
		int readByte = Serial1.read(); //read next available byte

		if (readByte == 2) reading = true; //begining of tag
		if (readByte == 3) reading = false; //end of tag

		if (reading && readByte != 2 && readByte != 3 && readByte != 10 && readByte != 13 && index < 12){
			bytesRead[index] = readByte;
			index++;
		}
		if (index == 12)bytesRead[12] = '\0';
	}

#ifdef DEBUG_MODE_RFID
	Serial.print("readTag: "); Serial.println(bytesRead);
#endif

	bool validRead = checkTagChecksum(bytesRead);
	if (validRead){
		memcpy(tag, bytesRead, 10);
	}

#ifdef DEBUG_MODE_RFID
	Serial.print("cardPresent: "); Serial.print(String(cardPresent)); Serial.print(" & validRead: "); Serial.println(String(validRead));
#endif

	return cardPresent && validRead;
}

bool InnovationsRFID::checkTagChecksum(char bytesRead[]){
	if (strlen(bytesRead) < 12){
#ifdef DEBUG_MODE_RFID
		Serial.println("bytesRead.len: " + String(strlen(bytesRead) < 12));
#endif        
		return false;
	}

	byte checksum = 0;
	for (int i = 0; i < 10; i = i + 2){
		checksum ^= (getASCICode(bytesRead[i + 1]) | (getASCICode(bytesRead[i]) << 4));
	}

	byte rchecksum = (getASCICode(bytesRead[11]) | (getASCICode(bytesRead[10]) << 4));

#ifdef DEBUG_MODE_RFID
	Serial.print("Checksum: ");
	Serial.print(checksum, HEX);
	Serial.print(" - ");
	Serial.print(rchecksum, HEX);
	Serial.println(checksum == rchecksum ? " -- passed." : " -- error.");
#endif

	return checksum == rchecksum;
}

byte InnovationsRFID::getASCICode(byte val){
	// Ascii/Hex conversion:
	if ((val >= '0') && (val <= '9')) {
		val = val - '0';
	}
	else if ((val >= 'A') && (val <= 'F')) {
		val = 10 + val - 'A';
	}

	return val;
}

///////////////////////////////////
//Reset the RFID reader to read again.
///////////////////////////////////
void InnovationsRFID::resetReader(){
	digitalWrite(RFIDResetPin, LOW);
	digitalWrite(RFIDResetPin, HIGH);
	delay(150);
}

///////////////////////////////////
//clear the char array by filling with null - ASCII 0
//Will think same tag has been read otherwise
///////////////////////////////////
void InnovationsRFID::clearTag(){
	for (int i = 0; i < strlen(tag); i++){
		tag[i] = 0;
	}
}

///////////////////////////////////
//compare two value to see if same,
//strcmp not working 100% so we do this
///////////////////////////////////
bool InnovationsRFID::compareTag(char one[], char two[]){
	if (strlen(one) == 0) return false; //empty

	for (int i = 0; i < 10; i++){
		if (one[i] != two[i]) return false;
	}

	return true; //no mismatches
}