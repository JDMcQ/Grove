#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MQTTClient.h>
#include <SimpleDHT.h>


//-------DHT---------
#define DHTPIN 2     // what digital pin we're connected to
SimpleDHT11 dht11;

float DT_202;
float DH_202;
char  *DT_202_str = "DT_202_str";
char  *DH_202_str = "DH_202_str";

//------- PIR ------------
#define PIR_203_PIN 5
int PIR_203 = 0;
char  *PIR_203_str = "PIR_203_str";

//------- Analog Pins --------
int reading;
int TT_201_Pin = 1;
float TT_201;
char  *TT_201_str = "TT_201_str";



// ----------------------   Ethernet setup ----------------
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 52);
IPAddress server(192, 168, 1, 50); //MQTT 'Broker'
EthernetServer Webserver(80);
EthernetClient net;

// ---------- MQTT --------------
MQTTClient mclient;
unsigned long lastMillis = 0;


void connect() {
  Serial.print("connecting...");
  while (!mclient.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  mclient.subscribe("/hello");
  // client.unsubscribe("/hello");
}


void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}


void setup() {

	//  ------------- Serial Setup ----------------
	Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
	// ---------------------------------------------


	// -----------------Pin Setups -----------------------------------
    analogReference(INTERNAL);
    pinMode(PIR_203_PIN, INPUT);
    // ---------------------------------------------------------------

    // -------------- Web server Setup  ------------------------------
    Ethernet.begin(mac, ip);
    Webserver.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
    // ---------------------------------------------------------------

    mclient.begin("192.168.1.50:1883", net);
    mclient.onMessage(messageReceived);

 //   connect();

}


void loop() {

  mclient.loop();

  // start working...
  Serial.println("==========");

//  ------------- DHT_202 Code ---------------------------------------------

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(DHTPIN, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
	  Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
	  return;
  }else{
	  double DT_202_dbl = ((double)temperature * 9.0/5.0 + 32.0);
	  double DH_202_dbl = ((double)humidity);
	  Serial.print(DT_202_dbl); Serial.println(" *F\r");
	  Serial.print((int)humidity); Serial.println(" %H\r");

	  dtostrf(DT_202_dbl,6,3,DT_202_str);
	  dtostrf(DH_202_dbl,6,3,DH_202_str);
  }

// -----------------------------------------------------------------------------


// -------------- TT_201 -------------------------------------------------------

  reading = analogRead(TT_201_Pin);
  TT_201 = reading / 9.31;
  Serial.print(TT_201); Serial.println(" *F Analog\r");

  dtostrf(TT_201,8,4,TT_201_str);
  Serial.print("An Temp:  "); Serial.print(DT_202_str); Serial.println( " *F Analog\r");

// ----------------------------------------------------------------------------------

// ----------- PIR CODE -----------------------

  PIR_203 = digitalRead(PIR_203_PIN);
  if (PIR_203 == HIGH){
	  Serial.println("Motion!\r");
	  PIR_203_str = "Motion!";
  }else{
	  Serial.println("Still...\r");
	  PIR_203_str = "Still...";
  }

// --------------------------------------------


//  ----------- Web Code ----------------------
  EthernetClient client = Webserver.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("<p> Temperature, TT_201: ");client.print(TT_201_str);client.println(" deg F </p>");
          client.print("<p> Temperature, DT_202: ");client.print(DT_202_str);client.println(" deg F </p>");
          client.print("<p> Temperature, DH_202: ");client.print(DH_202_str);client.println(" % H </p>");
          client.print("<p> Activity, PIR_203: ");client.print(PIR_203_str);client.println(" Boolean </p>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }



//  ----------------------------------------------------------------------------------------------------------------------------------------------------------







  delay(3000);

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
	  lastMillis = millis();
	  mclient.publish("/hello", "world");
  }

}
