#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE()

const int ledPins[] = {37, 35, 33, 31, 23, 25, 27, 29};
const int buttonPins[] = {36, 34, 32, 30, 22, 24, 26, 28};
int buttonStates[8] = {0};
int notes[8] = {0};
int channels[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int ctrlDefaults[] = {100, 101, 102, 103, 104, 105, 106, 107};
int ctrl[8];

const int buttonPin1 = 13;
const int buttonPin2 = 12;
int buttonState1 = 0, buttonState2 = 0;
int lastButtonState1 = 0, lastButtonState2 = 0;
int buttonPushCounter = 1;

void setup() {
    Serial.begin(31250);
    MIDI.begin(1);

    for (int i = 0; i < 8; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT);
        ctrl[i] = ctrlDefaults[i];
    }

    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
}

void loop() {
    for (int i = 0; i < 8; i++) {
        buttonStates[i] = digitalRead(buttonPins[i]);
        if (buttonStates[i] == HIGH) {
            if (notes[i] == 0) {
                digitalWrite(ledPins[i], HIGH);
                MIDI.sendControlChange(ctrl[i], 127, channels[i]);
                notes[i] = 1;
            }
        } else {
            if (notes[i] == 1) {
                digitalWrite(ledPins[i], LOW);
                MIDI.sendControlChange(ctrl[i], 0, channels[i]);
                notes[i] = 0;
            }
        }
    }

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

    if (buttonPushCounter < 0) {
        buttonPushCounter = 0;
    }
}
