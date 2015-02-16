# Buttons
Arduino pushbutton library

``` cpp
#include <Buttons.h>

const int DEBOUNCE_MILLIS = 50;
const int REPEAT_INITIAL_DELAY_MILLIS = 500;
const int REPEAT_DELAY_MILLIS = 100;

Button* button[] = { new DigitalButton(12, INPUT_PULLUP, DEBOUNCE_MILLIS, REPEAT_INITIAL_DELAY_MILLIS, REPEAT_DELAY_MILLIS, handleClick, handleRelease) };

void setup() {
	Serial.begin(9600);
	Serial.println("STARTING");
}

void loop() {
	button[0]->read();
}

void handleClick(Button* button) {
  Serial.println("CLICKED");
  Serial.println(button->isRepeating());
}

void handleRelease(Button* button) {
  Serial.println("RELEASED");
  Serial.println(button->isRepeating());
}
```

