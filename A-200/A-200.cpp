#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <MQTTClient.h>

//-------DHT---------
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 2     // what digital pin we're connected to

DHT DHT_201(2,DHTTYPE);  // OK Weird Syntax...
#define DHT_202_PIN 2
float DT_202;
float DH_202;

char  *DT_202_str = "Place holder";

//-------PIR---------
#define PIR_203_PIN 5
int PIR_203 = 0;

int reading;
int TT_201_Pin = 1;
float TT_201;


// ----------------------   Ethernet setup ----------------
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 52);
IPAddress server(192, 168, 1, 50); //MQTT 'Broker'
//EthernetServer Webserver(80);

// ---------------  MQTT ------------------------

//EthernetClient ethClient;
MQTTClient MQclient;

void callback(char* topic, byte* payload, unsigned int length) {
//void callback(char* topic, byte* payload, int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i=0; i<length ;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


//   ----------------- End MQTT ---------------------------------

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius){
  return 1.80 * celsius + 32.00;
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void connect() {
  Serial.print("connecting...");
  while (!MQclient.connect("ARD_200")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  MQclient.subscribe("/hello");
  // client.unsubscribe("/hello");MQ
}



void setup() {


    analogReference(INTERNAL);
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

 //   Ethernet.begin(mac, ip);
 //   Webserver.begin();
    Serial.print("server is at ");
//    Serial.println(Ethernet.localIP());

    pinMode(PIR_203_PIN, INPUT);

//    MQclient.begin( "192.168.1.50", ethClient);
    MQclient.onMessage(messageReceived);

    connect();
//  MQTT setup

//    MQTTClient client;
//    rc = MQTTClient_create(&client, "192.168.1.50:1883", "Ard_201" , MQTTCLIENT_PERSISTENCE_NONE, NULL);


}


void loop() {

    delay(2000);

     DH_202 = DHT_201.readHumidity();
     // Read temperature as Celsius (the default)
     //float t = dht.readTemperature();
     // Read temperature as Fahrenheit (isFahrenheit = true)
     DT_202 = DHT_201.readTemperature(true);


}
