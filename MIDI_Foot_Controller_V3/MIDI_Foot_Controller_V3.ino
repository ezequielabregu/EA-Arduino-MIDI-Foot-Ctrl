//SevenSegmentTM1637
// diodo 40
// cat 42
//CC EXPR Selector
// switch 1  pwm 13
// switch 2 pwm 12

#include "SevenSegmentTM1637.h"
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE ()

const int led1 = 37;
const int led2 = 35;
const int led3 = 33;
const int led4 = 31;
const int led5 = 23;
const int led6 = 25;
const int led7 = 27;
const int led8 = 29;


const int button1 = 36;
const int button2 = 34;
const int button3 = 32;
const int button4 = 30;
const int button5 = 22;
const int button6 = 24;
const int button7 = 26;
const int button8 = 28;


int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int button6State = 0;
int button7State = 0;
int button8State = 0;


int channel1 = 1;
int channel2 = 1;
int channel3 = 1;
int channel4 = 1;
int channel5 = 1;
int channel6 = 1;
int channel7 = 1;
int channel8 = 1;


int ctrl1Default = 100;  //CC# of button 1
int ctrl2Default = 101;
int ctrl3Default = 102;
int ctrl4Default = 103;
int ctrl5Default = 104;  //CC# of button 1
int ctrl6Default = 105;
int ctrl7Default = 106;
int ctrl8Default = 107;

int ctrl1 = 100;  //CC# of button 1
int ctrl2 = 101;
int ctrl3 = 102;
int ctrl4 = 103;
int ctrl5 = 104;  //CC# of button 1
int ctrl6 = 105;
int ctrl7 = 106;
int ctrl8 = 107;


int note1 = 0;
int note2 = 0;
int note3 = 0;
int note4 = 0;
int note5 = 0;
int note6 = 0;
int note7 = 0;
int note8 = 0;



//Variable for Potentiometer
int analogValue = 0;
int lastAnalogValue = 128; //Valor de inicio, se usa para comparar con el valor anterior11

/// Expression ctrl

// this constant won't change:
const int  buttonPin1 = 13;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 12;

// Variables will change:
int buttonPushCounter = 1;   // counter for the number of button presses

int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;

int lastButtonState1 = 0;     // previous state of the button
int lastButtonState2 = 0;     // previous state of the button

int CCnumber = 1;

//int analogValue=0;
//int lastAnalogValue=128; //Valor de inicio, se usa para comparar con el valor anterior


//display

const byte PIN_CLK = 42;  // define CLK pin (any digital pin)
const byte PIN_DIO = 40;  // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

int count1 = 0;
int count2 = 0;
int scene = 1;

int exprState = 0;
int lastExprState = 0;
int exprToggle = 0;

int ledIndex[8] = {37, 35, 33, 31, 23, 25, 27, 29};

void setup () {

  Serial.begin (31250);
  MIDI.begin (1);

  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led4, OUTPUT);
  pinMode (led5, OUTPUT);
  pinMode (led6, OUTPUT);
  pinMode (led7, OUTPUT);
  pinMode (led8, OUTPUT);


  pinMode (button1, INPUT);
  pinMode (button2, INPUT);
  pinMode (button3, INPUT);
  pinMode (button4, INPUT);
  pinMode (button5, INPUT);
  pinMode (button6, INPUT);
  pinMode (button7, INPUT);
  pinMode (button8, INPUT);

  // Expression ctrl

  pinMode(buttonPin1, INPUT_PULLUP);
  // initialize the LED as an output:
  pinMode(buttonPin2, INPUT_PULLUP);




  ///display
  display.begin();            // initializes the display
  display.setBacklight(100);
  display.print("ABREGU MIDI CTRL");      // display INIT on the display

  //ANIMACION LEDS
  for (int ledCount = 0; ledCount <= 8 ; ledCount++) {
    digitalWrite (ledIndex[ledCount] , HIGH);
    delay (80);
    digitalWrite (ledIndex[ledCount], LOW);
  }


  display.print("LOAD");
  display.blink ();
  display.clear();

}

void loop () {


  if (digitalRead (13) == HIGH) {
    count1 = ++count1;
    if (count1 == 500) {
      scene = 2;
      count1 = 0 ;
      buttonPushCounter = buttonPushCounter - 1; // para que vuelva al control que dejó al pulsar el btn
    }
    delay (1);
  }
  else {
    count1 = 0 ;
  }

  if (digitalRead (12) == HIGH) {
    count2 = ++count2;
    if (count2 == 500) {
      scene = 3;
      count2 = 0 ;
      buttonPushCounter = buttonPushCounter + 1; // para que vuelva al control que dejó al pulsar el btn
    }
    delay (1);
  }
  else {
    count2 = 0 ;
  }


  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);
  button5State = digitalRead(button5);
  button6State = digitalRead(button6);
  button7State = digitalRead(button7);
  button8State = digitalRead(button8);



  switch (scene) {
    //////***************/////

    case 1:



      //****Button & LED 1****//
      if (button1State == HIGH) {
        if (note1 == 0) {
          digitalWrite (led1, HIGH);
          MIDI.sendControlChange(ctrl1, 127, channel1);

          note1 = 1;
        }
      }
      else {
        if (note1 == 1) {
          digitalWrite(led1, LOW);
          MIDI.sendControlChange(ctrl1, 0, channel1);
          note1 = 0;
        }
      }

      //****Button & LED 2*****//
      if (button2State == HIGH) {
        if (note2 == 0) {
          digitalWrite (led2, HIGH);
          MIDI.sendControlChange(ctrl2, 127, channel2);
          note2 = 1;
        }
      }
      else {
        if (note2 == 1) {
          digitalWrite(led2, LOW);
          MIDI.sendControlChange(ctrl2, 0, channel2);
          note2 = 0;

        }
      }

      //****Button & LED 3*****//
      if (button3State == HIGH) {
        if (note3 == 0) {
          digitalWrite (led3, HIGH);
          MIDI.sendControlChange(ctrl3, 127, channel3);
          note3 = 1;
        }
      }
      else {
        if (note3 == 1) {
          digitalWrite(led3, LOW);
          MIDI.sendControlChange(ctrl3, 0, channel3);
          note3 = 0;
        }
      }

      //****Button & LED 4*****//
      if (button4State == HIGH) {
        if (note4 == 0) {
          digitalWrite (led4, HIGH);
          MIDI.sendControlChange(ctrl4, 127, channel4);
          note4 = 1;
        }
      }
      else {
        if (note4 == 1) {
          digitalWrite(led4, LOW);
          MIDI.sendControlChange(ctrl4, 0, channel4);
          note4 = 0;
        }
      }

      //****Button & LED 5****//
      if (button5State == HIGH) {
        if (note5 == 0) {
          digitalWrite (led5, HIGH);
          MIDI.sendControlChange(ctrl5, 127, channel5);

          note5 = 1;
        }
      }
      else {
        if (note5 == 1) {
          digitalWrite(led5, LOW);
          MIDI.sendControlChange(ctrl5, 0, channel5);
          note5 = 0;
        }
      }

      //****Button & LED 6*****//
      if (button6State == HIGH) {
        if (note6 == 0) {
          digitalWrite (led6, HIGH);
          MIDI.sendControlChange(ctrl6, 127, channel6);
          note6 = 1;
        }
      }
      else {
        if (note6 == 1) {
          digitalWrite(led6, LOW);
          MIDI.sendControlChange(ctrl6, 0, channel6);
          note6 = 0;

        }
      }

      //****Button & LED 7*****//
      if (button7State == HIGH) {
        if (note7 == 0) {
          digitalWrite (led7, HIGH);
          MIDI.sendControlChange(ctrl7, 127, channel7);
          note7 = 1;
        }
      }
      else {
        if (note7 == 1) {
          digitalWrite(led7, LOW);
          MIDI.sendControlChange(ctrl7, 0, channel7);
          note7 = 0;

        }
      }
      //****Button & LED 8*****//
      if (button8State == HIGH) {
        if (note8 == 0) {
          digitalWrite (led8, HIGH);
          MIDI.sendControlChange(ctrl8, 127, channel6);
          note8 = 1;
        }
      }
      else {
        if (note8 == 1) {
          digitalWrite(led8, LOW);
          MIDI.sendControlChange(ctrl8, 0, channel8);
          note8 = 0;

        }
      }
      //****EXPR Pedal****//

      ////escaleo el rango 0-1023
      //int analogValue= 127 -(abs(analogRead (0)/8));
      //
      // //si la diferencia entre lastAnalogValue y el Valor entrante (analogValue) es  > 1 o < -1
      // //entonces mando valor. Si no hay cambio, no mando nada.
      // if ((analogValue - lastAnalogValue) > 1 || (analogValue-lastAnalogValue) < -1) {
      //
      //  MIDI.sendControlChange( 1, analogValue, 1);
      //  lastAnalogValue = analogValue; // queda el ultimo valor del pote.
      //
      //   }
      //

      ///
      buttonState1 = digitalRead(buttonPin1);

      // compare the buttonState to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button
          // wend from off to on:
          buttonPushCounter++;

        }
        else {

        }
        // Delay a little bit to avoid bouncing
      }
      // save the current state as the last state,
      //for next time through the loop
      lastButtonState1 = buttonState1;

      //////////////////////////////////////////////////////////
      // read the pushbutton input pin:
      buttonState2 = digitalRead(buttonPin2);

      // compare the buttonState to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button
          // wend from off to on:
          buttonPushCounter--;

        }
        else {

        }
        // Delay a little bit to avoid bouncing
        //delay(50);
      }
      // save the current state as the last state,
      //for next time through the loop
      lastButtonState2 = buttonState2;

      //////////////LIMITO EL CCnro = 0

      if (buttonPushCounter < 0) {
        buttonPushCounter = 0;
      }
      /////////MIDI POTENTIOMETER/////////////////////////////////////////////////////////////



      CCnumber = buttonPushCounter;
      if (exprState == 1) {
        analogValue = analogRead (0) / 8;
      }
      else {
        analogValue = 0;
      }

      if (analogValue  != lastAnalogValue) {
        if ((analogValue < (lastAnalogValue - 1)) || (analogValue > (lastAnalogValue + 1))) {


          MIDI.sendControlChange( CCnumber, analogValue, 1);
          lastAnalogValue = analogValue; // queda el ultimo valor del pote.

        }

      }

      ///DISPLAY


      display.setCursor (0, 0);
      display.print("C ");
      if (buttonPushCounter < 10) {
        display.setCursor (0, 2);
        display.print("0");
        display.setCursor (0, 3);
        display.print(buttonPushCounter);
      }
      else {
        display.setCursor (0, 2);
        display.print(buttonPushCounter);
      }

      delay (1);

      break;
    /////////////////***********************/////////////////////////////
    case 2:
      display.setCursor (0, 0);
      display.print("SELECT ");
      display.clear();


      if (digitalRead (36) == HIGH) {
        ctrl1 = ctrl1Default;
        ctrl2 = ctrl2Default;
        ctrl3 = ctrl3Default;
        ctrl4 = ctrl4Default;
        ctrl5 = ctrl5Default;
        ctrl6 = ctrl6Default;
        ctrl7 = ctrl7Default;
        ctrl8 = ctrl8Default;
        delay (20);
        display.setCursor (0, 0);
        display.print("Scn1");
        display.blink();
        delay (500);
        scene = 1;
      }

      else if (digitalRead (34) == HIGH) {
        ctrl1 = ctrl1Default + 8;
        ctrl2 = ctrl2Default + 8;
        ctrl3 = ctrl3Default + 8;
        ctrl4 = ctrl4Default + 8;
        ctrl5 = ctrl5Default + 8;
        ctrl6 = ctrl6Default + 8;
        ctrl7 = ctrl7Default + 8;
        ctrl8 = ctrl8Default + 8;
        delay (20);
        display.setCursor (0, 0);
        display.print("Scn2");
        display.blink();
        delay (500);
        scene = 1;
      }

      else if (digitalRead (32) == HIGH) {
        ctrl1 = ctrl1Default + 16;
        ctrl2 = ctrl2Default + 16;
        ctrl3 = ctrl3Default + 16;
        ctrl4 = ctrl4Default + 16;
        ctrl5 = ctrl5Default + 16;
        ctrl6 = ctrl6Default + 16;
        ctrl7 = ctrl7Default + 16;
        ctrl8 = ctrl8Default + 16 ;
        delay (20);
        display.setCursor (0, 0);
        display.print("Scn3");
        display.blink();
        delay (500);
        scene = 1;
      }

      break;


    case 3:


      exprState = 1 - exprState;

      if (exprState == 1) {
        display.setCursor (0, 0);
        display.print("EXPR");
        delay (1000);
        display.print("ON  ");
        delay (1000);
        display.blink();
        scene = 1;

      }
      else {
        display.setCursor (0, 0);
        display.print("EXPR");
        delay (1000);
        display.print("OFF ");
        delay (1000);
        display.blink();
        scene = 1;
      }



      break;

  } // cierra switch

} // cierra void
