#include "stdio.h" 
#include <WiFi.h>

const char* ssid     = "**";
const char* password = "**";

WiFiServer server(80);

#define FORWARD_LEFT 25
#define REVERSE_LEFT 33

#define FORWARD_RIGHT 27
#define REVERSE_RIGHT 26

#define ECHO_PIN 14
#define TRIG_PIN 12


void setup() {
  Serial.begin(9600);
  pinMode(FORWARD_LEFT, OUTPUT) ;
  pinMode(REVERSE_LEFT, OUTPUT);
  pinMode(FORWARD_RIGHT, OUTPUT);
  pinMode(REVERSE_RIGHT, OUTPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT_PULLUP);
  Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}
void moveBackward();
void moveForward();
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {
    
    String req = client.readStringUntil('\r');
    client.flush();
    if (req.indexOf("/picture/1") != -1){
      moveBackward();
    }
    else if (req.indexOf("/picture/2") != -1){
      moveForward();
    }
  }
}





int getDistance(){
  digitalWrite(TRIG_PIN,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,HIGH);
  // The time it takes the ping to reflect on a surface 
  // and be picked up by the Echo
  int duration = pulseIn(ECHO_PIN, HIGH);
  
  // Simple v = d/t equation, with one constant.
  int distance = (duration/2)*0.0343;
  if (distance != 0) {
    Serial.println(distance);
    return distance;
    
    }
  }

void stopMove(){
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(REVERSE_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(REVERSE_RIGHT, LOW);
}

void moveBackward(){
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(REVERSE_LEFT, HIGH);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(REVERSE_RIGHT, HIGH);
}

void moveForward(){
  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(REVERSE_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(REVERSE_RIGHT, LOW);
}

void rotateLeft(){
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(REVERSE_LEFT, HIGH);
  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(REVERSE_RIGHT, LOW);
}

void rotateRight(){
  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(REVERSE_LEFT, LOW);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(REVERSE_RIGHT, HIGH);
}
