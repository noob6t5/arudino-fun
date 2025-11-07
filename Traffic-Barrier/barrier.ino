#include <Servo.h>

#define TRIG_PIN 8
#define ECHO_PIN 9
#define SERVO_PIN 10

Servo gate;

long duration;
int distance;
int threshold = 15; // cm
bool gateOpen = false;
unsigned long detectedTime = 0;
unsigned long gateTimer = 0;

void setup() {
  Serial.begin(9600);
  gate.attach(SERVO_PIN);
  gate.write(0); // start closed
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  // Object detected near sensor
  if (distance > 0 && distance < threshold) {
    if (!gateOpen) {
      openGateSmooth();
      gateTimer = millis(); // start timer when opened
    }

    // If object stays too long
    if (gateOpen && (millis() - gateTimer > 5000)) {
      closeGateSmooth();
    }
  }
  // Object moved away
  else {
    if (gateOpen) {
      if (detectedTime == 0) detectedTime = millis();
      if (millis() - detectedTime > 5000) {
        closeGateSmooth();
      }
    } else {
      detectedTime = 0;
    }
  }

  delay(200);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int cm = duration * 0.034 / 2;
  if (cm == 0 || cm > 200) return 200;
  return cm;
}

void openGateSmooth() {
  Serial.println("Gate Opening (smooth)...");
  for (int pos = 0; pos <= 90; pos++) {
    gate.write(pos);
    delay(map(pos, 0, 90, 20, 10)); // slow start, faster middle
  }
  gateOpen = true;
  detectedTime = 0;
}

void closeGateSmooth() {
  Serial.println("Gate Closing (smooth)...");
  for (int pos = 90; pos >= 0; pos--) {
    gate.write(pos);
    delay(map(90 - pos, 0, 90, 20, 10)); // same easing in reverse
  }
  gateOpen = false;
  detectedTime = 0;
}
