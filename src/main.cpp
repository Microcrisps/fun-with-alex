#include <Arduino.h>
#include "../conf/config.h"

void setup() {
  Serial.begin(115200);

  int freq = 5000;
  int resolution = 8;

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  return;
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
        Serial.println("YEW!!!");
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
    if (loopCount < ms(500)) {
      for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        ledcWrite(ledChannel, dutyCycle);
        delay(7);
      }
      for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
        ledcWrite(ledChannel, dutyCycle);
        delay(7);
      }
    } else {
      loopCount = 0;
    }
  }
}
