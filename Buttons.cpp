#include "Arduino.h"
#include "Buttons.h"

Button::~Button() {
  // destructor
}

// Digital button
DigitalButton::DigitalButton(int pin, byte pMode, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback) {
  _pin = pin;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = repeatInitialDelay;
  _repeatDelay = repeatDelay;
  _pinMode = pMode;
  pinMode(pin, _pinMode);
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
}

DigitalButton::DigitalButton(int pin, byte pMode, int debounceDelay, buttonCallbackType clickCallback) {
  _pin = pin;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = -1;
  _repeatDelay = -1;
  _pinMode = pMode;
  pinMode(pin, _pinMode);
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
}

DigitalButton::DigitalButton(int pin, byte pMode, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback) {
  _pin = pin;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = repeatInitialDelay;
  _repeatDelay = repeatDelay;
  _pinMode = pMode;
  pinMode(pin, _pinMode);
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
  _releaseCallback = releaseCallback;
}

DigitalButton::DigitalButton(int pin, byte pMode, int debounceDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback) {
  _pin = pin;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = -1;
  _repeatDelay = -1;
  _pinMode = pMode;
  pinMode(pin, _pinMode);
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
  _releaseCallback = releaseCallback;
}

DigitalButton::~DigitalButton() {
}

void DigitalButton::read() {
  int reading = digitalRead(_pin);
  if (_pinMode == INPUT_PULLUP) {
    reading = !reading;                          // Need "!" as LOW = pressed (internal pullup)
  }

  if (reading != _previousState) {               // If button has changed since last time
    _lastDebounceTime = millis();                // store the time it changed
  }
    
  if (reading != _currentState                   // If the reading is different
      && (millis() - _lastDebounceTime)          // and more than the debounce delay has elapsed
          > _debounceDelay) {                    // since it changed
    _currentState = reading;                     // Store this reading as the new state
    if (_currentState == HIGH) {                 // If button is pressed
      _clickCallback(this);                      // Handle the button press
    } else {                                     // Button is not pressed
      if (_releaseCallback != NULL) {            // If there is a release callback defined
        _releaseCallback(this);                  // call it
      }
      _repeating = false;                        // Clear the repeating flag on release
    }
  }
    
  if (reading == HIGH                            // If the button is pressed
      && _currentState == HIGH) {                // and it was pressed last time  
    if ((_repeatInitialDelay >= 0 &&             // and repeating is enabled
        !_repeating &&                           // and we're not currently repeating
        millis() - _lastDebounceTime             // and the repeatInitialDelay time has passed
          > _repeatInitialDelay) ||              // OR
         (_repeating &&                          // We are repeating
         millis() - _lastDebounceTime            // and the repeatDelayTime has passed
           > _repeatDelay)) {
      _repeating = true;                         // Now we are repeating
      _clickCallback(this);                      // Handle the button press
      _lastDebounceTime = millis();              // Move the debounce time along for the next repeat
    }
  }
  _previousState = reading;
}

boolean DigitalButton::isRepeating() {
  return _repeating;
}

boolean DigitalButton::isDown() {
  return _currentState == HIGH;
}

// Analog button
AnalogButton::AnalogButton(int pin, int vMin, int vMax, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback) {
  _pin = pin;
  _vMin = vMin;
  _vMax = vMax;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = repeatInitialDelay;
  _repeatDelay = repeatDelay;
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
}

AnalogButton::AnalogButton(int pin, int vMin, int vMax, int debounceDelay, buttonCallbackType clickCallback) {
  _pin = pin;
  _vMin = vMin;
  _vMax = vMax;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = -1;
  _repeatDelay = -1;
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
}

AnalogButton::AnalogButton(int pin, int vMin, int vMax, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback) {
  _pin = pin;
  _vMin = vMin;
  _vMax = vMax;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = repeatInitialDelay;
  _repeatDelay = repeatDelay;
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
  _releaseCallback = releaseCallback;
}

AnalogButton::AnalogButton(int pin, int vMin, int vMax, int debounceDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback) {
  _pin = pin;
  _vMin = vMin;
  _vMax = vMax;
  _debounceDelay = debounceDelay;
  _repeatInitialDelay = -1;
  _repeatDelay = -1;
  _currentState = 0;
  _previousState = 0;
  _lastDebounceTime = 0;
  _repeating = false;
  _clickCallback = clickCallback;
  _releaseCallback = releaseCallback;
}

AnalogButton::~AnalogButton() {
}

void AnalogButton::read() {
  int analogReading = analogRead(_pin);
  int reading;
  if (analogReading >= _vMin && analogReading < _vMax) {
    reading = HIGH;
  } else {
    reading = LOW;
  }

  if (reading != _previousState) {               // If button has changed since last time
    _lastDebounceTime = millis();                // store the time it changed
  }
    
  if (reading != _currentState                   // If the reading is different
      && (millis() - _lastDebounceTime)          // and more than the debounce delay has elapsed
          > _debounceDelay) {                    // since it changed
    _currentState = reading;                     // Store this reading as the new state
    if (_currentState == HIGH) {                 // If button is pressed
      _clickCallback(this);                      // Handle the button press
    } else {                                     // Button is not pressed
      if (_releaseCallback != NULL) {            // If there is a release callback defined
        _releaseCallback(this);                  // call it
      }
      _repeating = false;                        // Clear the repeating flag on release
    }
  }
    
  if (reading == HIGH                            // If the button is pressed
      && _currentState == HIGH) {                // and it was pressed last time  
    if ((_repeatInitialDelay >= 0 &&             // and repeating is enabled
        !_repeating &&                           // and we're not currently repeating
        millis() - _lastDebounceTime             // and the repeatInitialDelay time has passed
          > _repeatInitialDelay) ||              // OR
         (_repeating &&                          // We are repeating
         millis() - _lastDebounceTime            // and the repeatDelayTime has passed
           > _repeatDelay)) {
      _repeating = true;                         // Now we are repeating
      _clickCallback(this);                      // Handle the button press
      _lastDebounceTime = millis();              // Move the debounce time along for the next repeat
    }
  }
  _previousState = reading;
}

boolean AnalogButton::isRepeating() {
  return _repeating;
}

boolean AnalogButton::isDown() {
  return _currentState == HIGH;
}

