const int buttonPin = 26;
const int ledPin = 27;
const int ledChannel = 0;
const int checkTime = 100; // in ms

int ledState = 1;
int buttonState = 0;
int lastButtonState = 0;

long loopCount = 0;
long loopSpeed = 0;

const unsigned long debounceDelay = 20;
unsigned long lastDebounceTime = 0;
unsigned long startTime = 0;

// declare functions
int getLoopSpeed();
int ms(int timeInMs);
void checkBtnState(int reading);
void animateLed();
