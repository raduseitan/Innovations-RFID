<html>
<body>
    <b><big>Innovations-RFID</big></b>
    <p>Innovations ID-2 / ID-12 / ID-20 RFID Reader library for  Particle Core (formerly known as Spark Core).</p>
    <p></p>
    <p>This library is based on "Can You ID This? ID-20 RFID Reader + Arduino" example <a href="http://bildr.org/2011/02/rfid-arduino/">http://bildr.org/2011/02/rfid-arduino/</a> with some minor tweaks and checksum function added.</p>
    <p></p>
    <p>
        <b>Connections:</b><br />
    </p>
    <table>
        <tr>
            <td>RFID Pin</td>
            <td>Particle Core Pin</td>
        </tr>
        <tr>
            <td>11 (+5V)</td>
            <td>VIN</td>
        </tr>
        <tr>
            <td>1 (GND)</td>
            <td>GND</td>
        </tr>
        <tr>
            <td>7 (Format Selector)</td>
            <td>GND</td>
        </tr>
        <tr>
            <td>9 (D0)</td>
            <td>Rx</td>
        </tr>
        <tr>
            <td>2 (RES)</td>
            <td>D6</td>
        </tr>
    </table>
    <p>
        <img width="200" src="https://raw.githubusercontent.com/raduseitan/Innovations-RFID/master/DSC_0091.JPG" />
        <img width="200" src="https://raw.githubusercontent.com/raduseitan/Innovations-RFID/master/DSC_0093.JPG" /><br />
        <img width="200" src="https://raw.githubusercontent.com/raduseitan/Innovations-RFID/master/DSC_0094.JPG" />
        <img width="200" src="https://raw.githubusercontent.com/raduseitan/Innovations-RFID/master/DSC_0095.JPG" />
    </p>
    <p></p>
    <p>
        <b>Example:</b><br />
    </p>
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
</body>
</html>
