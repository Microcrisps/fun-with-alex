const int buttonPin = 27;
const int ledPin = 26;
const int checkTime = 100; // in ms
const int ledChannel = 0;

int ledState = 1;
int buttonState = 0;
int lastButtonState = 0;

int brightness = 0;
int fadeAmount = 5;

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
