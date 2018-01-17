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


void setup() {

    analogReference(INTERNAL);
    Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

}

int n = 0;

void loop() {

	reading = analogRead(TT_201_Pin);
	TT_201 = reading / 9.31;
	int retcode = sprintf(DT_202_str, "%f",TT_201);
 //    delay(2000);

     DH_202 = DHT_201.readHumidity();
     // Read temperature as Celsius (the default)
     //float t = dht.readTemperature();
     // Read temperature as Fahrenheit (isFahrenheit = true)
     DT_202 = DHT_201.readTemperature(true);
     Serial.print("New Series: \n\r");
     Serial.print("Formatted Temp: ");
     Serial.print(DT_202_str); Serial.print("   Code: "); Serial.print(retcode);
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

}
