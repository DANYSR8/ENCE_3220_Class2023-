/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 
#include <SoftwareSerial.h>

// The serial connection to the GPS module
SoftwareSerial ss(4, 3);     // RX and then Tx 


void setup(){
  Serial.begin(9600);
  ss.begin(9600);

    Serial.setTimeout(1000); // adjust to get all data read if needed 
}

void loop(){

  

//////////////Original Show All Data ////////////////

  while (ss.available() > 0){
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
    delay(1000);
  }
}

////////////////////////////////////////////////

/*
    if (gpsData == "$GPGGA"){
        Serial.println("Data Found 2");
    }

    if(Serial.find("$GPGGA")){
      Serial.println("Data Found");
    }
    else{
      Serial.println("nothing");
    }
  }
*/

/*
if (Serial.find("$GPGSA")) {
    Serial.println("Found!");
  }

*/
/*
if (Serial.available() > 0){
 data = Serial.readString();
 Serial.print(data);

  if ( data == "$GPGGA"){
      Serial.print("FOUND");
    }
}
*/

//////////Chat GPT Help 





