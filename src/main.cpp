#include <Arduino.h>
#include "../conf/config.h"

int fStartTime = 0;
int fDelay = 30; // 30 ms

void setup() {
  Serial.begin(115200);

  int freq = 5000;
  int resolution = 13;

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);

  pinMode(buttonPin, INPUT);
}

void loop() {
  if (!loopSpeed) {
    loopSpeed = getLoopSpeed();
  } else {
    int reading = digitalRead(buttonPin);
    checkBtnState(reading);
    animateLed();
    lastButtonState = reading;
  }
  loopCount++;
}

int getLoopSpeed() {
  if (!startTime) {
    startTime = millis();
  } else if((millis() - startTime) > checkTime) { // 0.1 miliseconds
    loopSpeed = loopCount / checkTime; // get loop count per milisecond
    loopCount = 0;
  }
  return loopSpeed;
}

int ms(int timeInMs) {
  return (timeInMs * loopSpeed);
}

void checkBtnState(int reading) {
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
}

void animateLed() {
  if (ledState) {
    if (loopCount < ms(100)) {
      ledcWrite(ledChannel, 255);
    } else if(loopCount < ms(200)) {
      ledcWrite(ledChannel, 0);
    } else {
      loopCount = 0;
    }
  } else {
    unsigned long now = millis();
    if (!fStartTime) {
      fStartTime = now;
    } else if ((now - fStartTime) > fDelay) {
      int valueMax = 255;
      // calculate duty, 8191 from 2 ^ 13 - 1
      uint32_t duty = (8191 / valueMax) * min(brightness, valueMax);
      // write duty to LEDC
      ledcWrite(ledChannel, duty);
      brightness = brightness + fadeAmount;
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
      fStartTime = now;
    }
    loopCount = 0;
  }
}
