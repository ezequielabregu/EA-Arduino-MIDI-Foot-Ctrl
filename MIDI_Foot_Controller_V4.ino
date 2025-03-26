// Revision 26.03.2025

#include <MIDI.h>
#include <TM1637Display.h>
#include <Bounce2.h> // Librería para debounce

MIDI_CREATE_DEFAULT_INSTANCE();

const int ledPins[] = {37, 35, 33, 31, 23, 25, 27, 29};
const int buttonPins[] = {36, 34, 32, 30, 22, 24, 26, 28};
int notes[8] = {0};
int ctrlDefaults[] = {100, 101, 102, 103, 104, 105, 106, 107};
int ctrl[8];

const int buttonPin1 = 13;
const int buttonPin2 = 12;
int midiChannel = 1;
int lastDisplayedChannel = -1;

const byte PIN_CLK = 42;
const byte PIN_DIO = 40;
TM1637Display display(PIN_CLK, PIN_DIO);

const uint8_t CH_SEGMENTS[] = {0b00111001, 0b01110110};  // "C" y "H" en 7 segmentos

// Instancias de Bounce para debounce de botones
Bounce buttonBounce[8];
Bounce button1 = Bounce();
Bounce button2 = Bounce();

void setup() {
    Serial.begin(31250);
    MIDI.begin(1);

    for (int i = 0; i < 8; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT_PULLUP);
        ctrl[i] = ctrlDefaults[i];

        buttonBounce[i].attach(buttonPins[i]);
        buttonBounce[i].interval(10); // 10 ms de debounce

        // 📌 Leer el estado inicial de cada botón
        if (digitalRead(buttonPins[i]) == LOW) { // Activo en LOW
            digitalWrite(ledPins[i], HIGH);
            MIDI.sendControlChange(ctrl[i], 127, midiChannel);
            notes[i] = 1;
        } else {
            digitalWrite(ledPins[i], LOW);
            notes[i] = 0;
        }
    }

    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);

    button1.attach(buttonPin1);
    button1.interval(20); // 20 ms de debounce

    button2.attach(buttonPin2);
    button2.interval(20); // 20 ms de debounce
    
    display.setBrightness(7);
    display.setSegments(CH_SEGMENTS, 2, 0); // "CH"
    display.showNumberDecEx(midiChannel, 0b01000000, false, 2, 2);
}

void loop() {
    // Actualiza el estado de los botones con debounce
    for (int i = 0; i < 8; i++) {
        buttonBounce[i].update();
        if (buttonBounce[i].fell()) { // Detecta pulsación
            digitalWrite(ledPins[i], HIGH);
            MIDI.sendControlChange(ctrl[i], 127, midiChannel);
            notes[i] = 1;
        } 
        if (buttonBounce[i].rose()) { // Detecta liberación
            digitalWrite(ledPins[i], LOW);
            MIDI.sendControlChange(ctrl[i], 0, midiChannel);
            notes[i] = 0;
        }
    }

    // Actualiza botones de cambio de canal MIDI
    button1.update();
    button2.update();

    if (button1.fell()) { // Botón 1 presionado
        midiChannel++;
        if (midiChannel > 16) midiChannel = 16;
    }

    if (button2.fell()) { // Botón 2 presionado
        midiChannel--;
        if (midiChannel < 1) midiChannel = 1;
    }
    
    // Actualiza la pantalla solo si el canal cambió
    if (midiChannel != lastDisplayedChannel) {
        display.setSegments(CH_SEGMENTS, 2, 0); // "CH"
        display.showNumberDecEx(midiChannel, 0b01000000, false, 2, 2);
        lastDisplayedChannel = midiChannel;
    }
}
