/*
  Buttons.h - Library for working with buttons
*/
#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

/*
  Interface for a button
*/
class Button {
  public:
    virtual ~Button();
    virtual void read()=0;
    virtual boolean isRepeating()=0;
    virtual boolean isDown()=0;
};

typedef void (*buttonCallbackType)(Button*);

/*
  A digital button.  This type of button is connected to a digital pin in either INPUT or INPUT_PULLUP mode.
*/
class DigitalButton : public Button {
  public:
    DigitalButton(int pin, byte pinMode, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback);
    DigitalButton(int pin, byte pinMode, int debounceDelay, buttonCallbackType clickCallback);
    DigitalButton(int pin, byte pinMode, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback);
    DigitalButton(int pin, byte pinMode, int debounceDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback);
    ~DigitalButton();
    void read();
    boolean isRepeating();
    boolean isDown();

  private:
    int _pin;
    byte _pinMode;
    int _currentState;
    int _previousState;
    long _lastDebounceTime;
    int _debounceDelay;
    int _repeatInitialDelay;
    int _repeatDelay;
    boolean _repeating;
    buttonCallbackType _clickCallback;
    buttonCallbackType _releaseCallback = NULL;
};

class AnalogButton : public Button {
  public:
    AnalogButton(int pin, int vMin, int vMax, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback);
    AnalogButton(int pin, int vMin, int vMax, int debounceDelay, buttonCallbackType clickCallback);
    AnalogButton(int pin, int vMin, int vMax, int debounceDelay, int repeatInitialDelay, int repeatDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback);
    AnalogButton(int pin, int vMin, int vMax, int debounceDelay, buttonCallbackType clickCallback, buttonCallbackType releaseCallback);
    ~AnalogButton();
    void read();
    boolean isRepeating();
    boolean isDown();

  private:
    int _pin;
    int _vMin;
    int _vMax;
    int _currentState;
    int _previousState;
    long _lastDebounceTime;
    int _debounceDelay;
    int _repeatInitialDelay;
    int _repeatDelay;
    boolean _repeating;
    buttonCallbackType _clickCallback;
    buttonCallbackType _releaseCallback = NULL;
};

#endif
