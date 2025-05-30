#include <ESP32Servo.h>

#define trigPin 2
#define echoPin 15
#define buzzerPin 4 // Buzzer sur GPIO23

long duration;
int distance;

Servo myservo;

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void buzz(int dist) {
  if (dist > 50 || dist == 0) {
    noTone(buzzerPin); // Ne pas émettre de son
    return;
  }

  int delayTime;
  if (dist <= 10) delayTime = 100;
  else if (dist <= 30) delayTime = 300;
  else delayTime = 600;

  tone(buzzerPin, 1000); // émettre un son de 1kHz
  delay(50);             // durée du bip
  noTone(buzzerPin);
  delay(delayTime);      // pause selon la distance
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  myservo.attach(13);
  Serial.begin(9600);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myservo.write(i);
    delay(10);
    int dist = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(dist);
    Serial.print(".");
    buzz(dist); // contrôle du buzzer
  }

  for (int i = 165; i >= 15; i--) {
    myservo.write(i);
    delay(10);
    int dist = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(dist);
    Serial.print(".");
    buzz(dist); // contrôle du buzzer
  }
}
