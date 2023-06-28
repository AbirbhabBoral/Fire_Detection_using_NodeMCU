#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "WiFI_Name"; 
char pass[] = "WiFi_Password"; 
BlynkTimer timer;

#define fire D2
#define GREEN D5
#define RED D6
#define buzzer  D7
int fire_Val = 0;
WidgetLED led(V1);
void setup() {
  Serial.begin(9600); 
  pinMode(GREEN, OUTPUT);
  pinMode(fire, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzer, OUTPUT); 
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(500L, mySensor);
}
void loop() {
  Blynk.run();
  timer.run();
}
void mySensor() {
  fire_Val = digitalRead(fire); 
  if (fire_Val == 0) {
    Blynk.logEvent("fire_event");
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(buzzer, HIGH);
    Blynk.virtualWrite(V0, 1);
    Serial.print("Fire Level: ");
    Serial.println(fire_Val);
    led.on();
  }
  else {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(buzzer, LOW);
    Blynk.virtualWrite(V0, 0);
    Serial.print("Fire Level: ");
    Serial.println(fire_Val);
    led.off();
  }    
}