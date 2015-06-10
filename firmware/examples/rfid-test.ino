// This #include statement was automatically added by the Particle IDE.
#include "innovations-rfid/innovations-rfid.h"

#define RFIDResetPin D6
#define DEBUG_MODE

char tag1[11] = "6A008FB104";
char tag2[11] = "0B002CB350";

InnovationsRFID rfid = InnovationsRFID();

void setup() {
    Serial.begin(9600);
#ifdef DEBUG_MODE    
    for (int i=0;i<50;i++){
		delay(200);
    }
#endif
    pinMode(D7, OUTPUT); //output to signal valid card
    
    rfid.setupRFID(RFIDResetPin);
}

void loop() {
    if(rfid.readTag()){
#ifdef DEBUG_MODE        
        Serial.print(rfid.tag); Serial.print(": ");
#endif        
        checkTag(rfid.tag); //Check if it is a match
        rfid.clearTag(); //Clear the char of all value
    }
    else{
        delay(200);
#ifdef DEBUG_MODE
        Serial.println("no tag present");
        delay(200);
#endif
    }
    
#ifdef DEBUG_MODE
    Serial.println("");
#endif
    
    rfid.clearTag();
    rfid.resetReader(); //reset the RFID reader
}

///////////////////////////////////
//Check the read tag against known tags
///////////////////////////////////
void checkTag(char tag[]){
    if(strlen(tag) == 0) return; //empty, no need to contunue
    
    if(rfid.compareTag(tag, tag1)){
        Serial.println("small tag");
        blinkLED(true);
    }
    else{
        if(rfid.compareTag(tag, tag2)){
            Serial.println("blue tag");
            blinkLED(true);
        }
        else{
            Serial.println("tag not matched");
            blinkLED(false);
        }
    }
}

void blinkLED(bool fast){
    for(int i=0;i<4;i++){
        digitalWrite(D7, HIGH);
        delay(fast?250:500);              
        digitalWrite(D7, LOW);
        delay(fast?250:500);            
    }
}
