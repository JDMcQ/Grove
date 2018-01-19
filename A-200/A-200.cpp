#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
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

EthernetClient net;

// MQTT
MQTTClient client;
unsigned long lastMillis = 0;


void connect() {
  Serial.print("connecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}


void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}


void setup() {

    analogReference(INTERNAL);
    Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    Ethernet.begin(mac, ip);
    client.begin("192.168.1.50:1883", net);
    client.onMessage(messageReceived);

    connect();

}

int n = 0;

void loop() {

	client.loop();

	if (!client.connected()) {
	  connect();
	}

	reading = analogRead(TT_201_Pin);
	TT_201 = reading / 9.31;
//	int retcode = sprintf(DT_202_str, " Formatted Value: %6.4f",TT_201);
 //    delay(2000);

     DH_202 = DHT_201.readHumidity();
     // Read temperature as Celsius (the default)
     //float t = dht.readTemperature();
     // Read temperature as Fahrenheit (isFahrenheit = true)
     DT_202 = DHT_201.readTemperature(true);
     dtostrf(TT_201,8,4,DT_202_str);
     //int retcode = sprintf(DT_202_str, ": %6.4f",DT_202);
     Serial.print("New Series: \n\r");
     Serial.print("Formatted Temp: ");
     Serial.print(DT_202_str); Serial.print("   Code: "); //Serial.print(retcode);
     Serial.print("\n\r");
     Serial.print("\n\r");
     Serial.print("Analog Temp: ");
     Serial.print(TT_201);
     Serial.print("\n\r");
     Serial.print("Temperature: ");
     Serial.print(DT_202);
     Serial.print("\n\r");
     Serial.print("   Humidity: ");
     Serial.print(DH_202);
     Serial.print("\n\r");
     Serial.print("\n\r");
     delay(2000);

     // publish a message roughly every second.
     if (millis() - lastMillis > 1000) {
       lastMillis = millis();
       client.publish("/hello", "world");
     }

}
