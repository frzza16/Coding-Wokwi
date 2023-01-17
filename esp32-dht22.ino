#include <WiFi.h>
#include <DHTesp.h>
#include "ThingSpeak.h"
#include <Adafruit_Sensor.h>

const int DHT_PIN = 15;
const char* ssid = "Wokwi-GUEST";
const char* pass = "";

WiFiClient client;

unsigned long myChannelNumber = 2;
const char* myWriteAPIKey = "MKKV9RZ6NWPWA5XI ";
const char* server = "api.thingspeak.com";

unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

int temperatureC;
int humidity;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  dhtSensor.getPin();
  delay(10);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connect");
  }
  Serial.println("WiFi Connect");
  Serial.println(WiFi.localIP());

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);

}
 void loop() {
   temperatureC = dhtSensor.getTemperature();
   Serial.println("Temperature ('C): ");
   Serial.println(temperatureC);
   humidity = dhtSensor.getHumidity();
   Serial.println("Humidity (%); ");
   Serial.println(humidity);

   ThingSpeak.setField(1, temperatureC);
   ThingSpeak.setField(2, humidity);

   int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
   if (x == 200) {
     Serial.println("Sukses");
   }
   else {
     Serial.println("Tunggu 15 Detik.... " + String(x));
   }
 }