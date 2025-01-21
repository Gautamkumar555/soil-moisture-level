#define BLYNK_TEMPLATE_ID "TMPL3u8gcpRVz"
#define BLYNK_TEMPLATE_NAME "soil monitoring system"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "WiFi Username";  // type your WiFi name
char pass[] = "WiFi Password";  // type your WiFi password

BlynkTimer timer;

void sendSensor()
{
  int value = analogRead(A0);
  value = map(value, 400, 1023, 100, 0); // Map values to 0-100 range
  if (value < 0) value = 0; // Ensure minimum value is 0
  if (value > 100) value = 100; // Ensure maximum value is 100
  
  Blynk.virtualWrite(V0, value); // Send soil moisture value to Blynk
  Serial.print("Soil Moisture: ");
  Serial.println(value);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor); // Update sensor value every second
}

void loop()
{
  Blynk.run();
  timer.run();
}
