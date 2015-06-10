
    ```cpp
    
    #include "innovations-rfid/innovations-rfid.h"
    #define RFIDResetPin D6

    InnovationsRFID rfid = InnovationsRFID();

    void setup() {
        Serial.begin(9600);
        rfid.setupRFID(RFIDResetPin);
    }

    void loop() {
        if(rfid.readTag()){
            Serial.print(rfid.tag);
            rfid.clearTag(); //Clear the char of all value
        }
        else{
            Serial.println("no tag present");
        }
    }

    ```

