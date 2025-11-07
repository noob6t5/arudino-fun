# arudino-fun
just for arudino fun projects

# NOte: Codee might not be my own

# Movement Cheatsheet for servo

```#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(3); // Servo signal pin
  Serial.begin(9600);
}

void loop() {

  // --------------------------
  // CASE 1: Instant stop mid-sweep
  // --------------------------
  Serial.println("Case 1: Stop mid-sweep");
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(15);
    if (pos == 45) {
      Serial.println("Stop at 45° for 2 seconds");
      delay(2000); // pause mid-way
    }
  }
  delay(1000);

  // --------------------------
  // CASE 2: Slow up/down sweep
  // --------------------------
  Serial.println("Case 2: Slow up/down sweep");
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(30); // slow up
  }
  for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(30); // slow down
  }
  delay(1000);

  // --------------------------
  // CASE 3: Fast up/down sweep
  // --------------------------
  Serial.println("Case 3: Fast up/down sweep");
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(5); // fast up
  }
  for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(5); // fast down
  }
  delay(1000);

  // --------------------------
  // CASE 4: Smooth full 180° sweep (slow)
  // --------------------------
  Serial.println("Case 4: Slow 180° sweep");
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(20);
  }
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(20);
  }
  delay(1000);

  // --------------------------
  // CASE 5: Fast full 180° sweep
  // --------------------------
  Serial.println("Case 5: Fast 180° sweep");
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(5);
  }
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(5);
  }
  delay(1000);

  // --------------------------
  // CASE 6: Continuous random movement (like alive)
  // --------------------------
  Serial.println("Case 6: Random start/stop movement");
  for (int i = 0; i < 3; i++) { // repeat a few times
    int target = random(0, 180);
    int speed = random(5, 25); // delay between steps
    Serial.print("Move to "); Serial.print(target); Serial.print("° at speed "); Serial.println(speed);

    if (myServo.read() < target) {
      for (int pos = myServo.read(); pos <= target; pos++) {
        myServo.write(pos);
        delay(speed);
      }
    } else {
      for (int pos = myServo.read(); pos >= target; pos--) {
        myServo.write(pos);
        delay(speed);
      }
    }

    // random pause
    int pauseTime = random(500, 2000);
    Serial.print("Pause for "); Serial.println(pauseTime);
    delay(pauseTime);
  }

  delay(1000);
}

```
