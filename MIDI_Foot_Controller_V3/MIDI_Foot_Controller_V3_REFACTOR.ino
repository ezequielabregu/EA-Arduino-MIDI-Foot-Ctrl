#include "SevenSegmentTM1637.h"
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int ledPins[] = {37, 35, 33, 31, 23, 25, 27, 29};
const int buttonPins[] = {36, 34, 32, 30, 22, 24, 26, 28};
int buttonStates[8] = {0};
int noteStates[8] = {0};
int channels[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int ctrlDefaults[] = {100, 101, 102, 103, 104, 105, 106, 107};
int ctrlValues[8];

const int buttonPin1 = 13, buttonPin2 = 12;
int buttonPushCounter = 1;
int buttonState1 = 0, buttonState2 = 0;
int lastButtonState1 = 0, lastButtonState2 = 0;
int CCnumber = 1;

const byte PIN_CLK = 42, PIN_DIO = 40;
SevenSegmentTM1637 display(PIN_CLK, PIN_DIO);
int scene = 1;
int exprState = 0, lastExprState = 0, exprToggle = 0;
int analogValue = 0, lastAnalogValue = 128;

void setup() {
    Serial.begin(31250);
    MIDI.begin(1);
    
    for (int i = 0; i < 8; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT);
        ctrlValues[i] = ctrlDefaults[i];
    }
    
    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
    
    display.begin();
    display.setBacklight(100);
    display.print("ABREGU MIDI CTRL");
    
    for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], HIGH);
        delay(80);
        digitalWrite(ledPins[i], LOW);
    }
    
    display.print("LOAD");
    display.blink();
    display.clear();
}

void loop() {
    handleSceneSelection();
    readButtonStates();
    handleLEDandMIDI();
    handleExpressionControl();
}

void handleSceneSelection() {
    static int count1 = 0, count2 = 0;
    
    if (digitalRead(buttonPin1) == HIGH) {
        if (++count1 == 500) {
            scene = 2;
            count1 = 0;
            buttonPushCounter--;
        }
    } else count1 = 0;
    
    if (digitalRead(buttonPin2) == HIGH) {
        if (++count2 == 500) {
            scene = 3;
            count2 = 0;
            buttonPushCounter++;
        }
    } else count2 = 0;
}

void readButtonStates() {
    for (int i = 0; i < 8; i++) {
        buttonStates[i] = digitalRead(buttonPins[i]);
    }
}

void handleLEDandMIDI() {
    if (scene != 1) return;
    
    for (int i = 0; i < 8; i++) {
        if (buttonStates[i] == HIGH) {
            if (noteStates[i] == 0) {
                digitalWrite(ledPins[i], HIGH);
                MIDI.sendControlChange(ctrlValues[i], 127, channels[i]);
                noteStates[i] = 1;
            }
        } else {
            if (noteStates[i] == 1) {
                digitalWrite(ledPins[i], LOW);
                MIDI.sendControlChange(ctrlValues[i], 0, channels[i]);
                noteStates[i] = 0;
            }
        }
    }
}

void handleExpressionControl() {
    buttonState1 = digitalRead(buttonPin1);
    if (buttonState1 != lastButtonState1 && buttonState1 == HIGH) {
        buttonPushCounter++;
    }
    lastButtonState1 = buttonState1;

    buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 != lastButtonState2 && buttonState2 == HIGH) {
        buttonPushCounter--;
    }
    lastButtonState2 = buttonState2;
    
    if (buttonPushCounter < 0) buttonPushCounter = 0;
    CCnumber = buttonPushCounter;
    
    if (exprState == 1) {
        analogValue = analogRead(0) / 8;
    } else {
        analogValue = 0;
    }
    
    if (abs(analogValue - lastAnalogValue) > 1) {
        MIDI.sendControlChange(1, analogValue, 1);
        lastAnalogValue = analogValue;
    }
}
