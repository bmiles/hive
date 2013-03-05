#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Cosm.h>

int lightOutPin = 3;
int tempOutPin = 5;
int soundOutPin = 6;
int stompOutPin = 9;

int lightVal = 0;
int tempVal = 0;
int soundVal = 0;
int stompVal = 0;

int motorSpeed1 = 0;
// MAC address for your Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Your Cosm key to let you upload data
char cosmKey[] = "SnTw4RSzpDXcmnoPxOuGBlCXRpWSAKxDTmh5Y0laaERhdz0g";

// Define the strings for our datastream IDs
// Create the 4 feeds
char sensorId[] = "Sound";
char sensorId2[] = "Temp";
char sensorId3[] = "Light";
char sensorId4[] = "Stomp";

// DATASTREAM_INT = integer
// DATASTREAM_FLOAT = float

CosmDatastream datastreams[] = {
  CosmDatastream(sensorId, strlen(sensorId), DATASTREAM_INT),  // define this ID in cosm
  CosmDatastream(sensorId2, strlen(sensorId), DATASTREAM_INT), // define this ID in cosm
  CosmDatastream(sensorId3, strlen(sensorId), DATASTREAM_INT), // define this ID in cosm
  CosmDatastream(sensorId4, strlen(sensorId), DATASTREAM_INT),
};
// Finally, wrap the datastreams into a feed
CosmFeed feed(103534, datastreams, 4 /* number of datastreams */);

// I use static IP address for easy troubleshooting
IPAddress ip(192,168,0,52);             // Static IP address

EthernetClient client;
CosmClient cosmclient(client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Reading from Cosm example");
  Serial.println();

  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
}

void loop() {
  int ret = cosmclient.get(feed, cosmKey);
  Serial.print("cosmclient.get returned ");
  Serial.println(ret);

  if (ret > 0)
  {
    
    //sound
      Serial.println("Datastream is...");
    Serial.println(feed[0]);

    Serial.print("sound is: ");
    Serial.println(feed[0].getFloat());
    soundVal = feed[0].getInt();
    Serial.println(soundVal);
    
    //temp
    
    Serial.println("Datastream is...");
    Serial.println(feed[1]);

    Serial.print("Temperature is: ");
    Serial.println(feed[1].getFloat());
    tempVal = feed[1].getInt();
        Serial.println(tempVal);
        
        //light

    Serial.println("Datastream is...");
    Serial.println(feed[2].getInt());

    Serial.print("light is: ");
    Serial.println(feed[2]);
    lightVal = feed[2].getInt();
    
    
    //stomp
    
    Serial.println("Datastream is...");
    Serial.println(feed[3]);
    

    Serial.print("Stomp is: ");
    Serial.println(feed[3].getFloat());
    stompVal = feed[3].getInt();
    Serial.print(stompVal);
  }
  //lightout
  if (lightVal > 900)
  {
    analogWrite(9,255);
  }
  else if (lightVal < 900 && lightVal > 500){
    analogWrite(9,255);
  }
  else if (lightVal < 500 && lightVal > 200){
    analogWrite(9,128);
  }
  else{
        analogWrite(9,64);
  };
  
  //volumeout
  motorSpeed1 = map(soundVal, 300, 1000, 1, 255);
  analogWrite(6, motorSpeed1);
  Serial.println(motorSpeed1);
  
 /*   if (soundVal > 900)
  {
    analogWrite(9,255);
  }
  else if (soundVal < 900 && soundVal > 500){
    analogWrite(9,255);
  }
  else if (soundVal < 500 && soundVal > 200){
    analogWrite(9,128);
  }
  else{
        analogWrite(9,64);
  };*/



  Serial.println();
  delay(15000UL);
}
