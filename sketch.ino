#include <Servo.h>

const int potPin = A0; // Pin potensiometer
const int servoPin = 9; // Pin servo
const int led1Pin = 10; // Pin LED1
const int led2Pin = 11; // Pin LED2

Servo myServo;
int potValue;
int servoPos;
int led1Brightness;
int led2Brightness;

void setup() {
  myServo.attach(servoPin);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  // Baca nilai dari potensiometer
  potValue = analogRead(potPin);
  
  // Konversi nilai potensiometer (0-1023) menjadi posisi servo (0-180)
  servoPos = map(potValue, 0, 1023, 0, 180);
  myServo.write(servoPos);
  
  // Tentukan batas-batas untuk LED
  int lowerThreshold = 60; // Anggap sebagai batas bawah
  int upperThreshold = 120; // Anggap sebagai batas atas

  if (servoPos < lowerThreshold) {
    // Posisi servo di bawah threshold, LED1 menyala, LED2 mati
    led1Brightness = map(servoPos, 0, lowerThreshold, 255, 0);
    led2Brightness = 0;
  } else if (servoPos > upperThreshold) {
    // Posisi servo di atas threshold, LED2 menyala, LED1 mati
    led1Brightness = 0;
    led2Brightness = map(servoPos, 180, upperThreshold, 0, 255);
  } else {
    // Posisi servo di tengah, kedua LED mati
    led1Brightness = 0;
    led2Brightness = 0;
  }

  // Atur kecerahan LED dengan PWM
  analogWrite(led1Pin, led1Brightness);
  analogWrite(led2Pin, led2Brightness);

  // Tunggu sebentar sebelum pembacaan berikutnya
  delay(15);
}
