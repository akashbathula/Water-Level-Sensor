#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
const char* ssid = "ACT101011917172"; // Enter your Wifi name
const char* password = "********"; // Enter wifi password
char auth[] = " HA9POp76levA3eObeNHwAuVrQy6Qa9Xk"; // Enter the Auth Token provied by Blynk app
const int trigPin = 22;
const int echoPin = 4;
const int led_red = 2;
const int led_yellow = 5;
const int led_green = 19;
const int l = 32;
float one_fourth_rem, half_rem, three_fourth_rem;
WidgetLCD lcd(V1);


void setup() {
  // put your setup code here, to run once:
  one_fourth_rem = 0.75 * l;
  half_rem = 0.5 * l;
  three_fourth_rem = 0.25 * l;
  Blynk.begin(auth, ssid, password);
  lcd.clear();
  lcd.print(0, 0, "Sensor readings in cm:");

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
  digitalWrite(led_red, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.clear();
  lcd.print(0, 0, "Sensor readings in cm:");
  long duration, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 29) / 2;

  //Serial.print("Distance is ");
  Serial.print("Distance still to be filled is : ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  lcd.print(7, 1, cm);
  Blynk.run();
  if (cm >= (one_fourth_rem - 3) && cm <= (one_fourth_rem)) {
    Serial.println("25% full");
  }
  else if (cm >= (half_rem - 3) && cm <= (half_rem)) {
    Serial.println("50% full");
  }
  else if (cm >= (three_fourth_rem - 3) && cm <= (three_fourth_rem)) {
    Serial.println("75% full");
  }

  if (cm > (one_fourth_rem)) {
    //Blynk.notify("Switch Pressed");
    digitalWrite(led_red, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_green, LOW);
  }

  else if (cm >= (one_fourth_rem - 3) && cm <= (one_fourth_rem)) {
    Serial.print("25% full");
    Blynk.notify("25% full");
    digitalWrite(led_red, HIGH);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_green, LOW);
  }
  else if (cm >= (half_rem - 3) && cm <= (half_rem)) {
    Serial.print("50% full");
    Blynk.notify("50% full");
    digitalWrite(led_red, HIGH);
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_green, LOW);
  }
  else if (cm <= (three_fourth_rem)) {
    Serial.print("75% full");
    Blynk.notify("75% full");
    digitalWrite(led_red, HIGH);
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_green, HIGH);
  }
  delay(2000);

}
