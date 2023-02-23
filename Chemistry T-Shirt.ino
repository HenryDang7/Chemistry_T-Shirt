// Libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Hardware Information
#define HARDWARE MD_MAX72XX::FC16_HW
#define SEGMENTS 4

#define DIN_ONE 10
#define CS_ONE 11
#define CLK_ONE 13

#define DIN_TWO 5
#define CS_TWO 3
#define CLK_TWO 2

// Pins
int switchPin = 4;
int lightPinOne = 7;
int lightPinTwo = 8;

// Variables
MD_Parola topDisplay = MD_Parola(HARDWARE, DIN_ONE, CLK_ONE, CS_ONE, SEGMENTS);
MD_Parola bottomDisplay = MD_Parola(HARDWARE, DIN_TWO, CLK_TWO, CS_TWO, SEGMENTS);

int currentState = 0;
bool previouslyActivated = false;

int cycleTimeElapsed = 0;

// Functions
void startTimer() {
  for (int i = 10; i >= 0; i--) {
    bottomDisplay.print(i);
    delay(1000);
  }

  bottomDisplay.print(";D");
}

// Main Functions
void setup() {
  pinMode(switchPin, INPUT);
  pinMode(lightPinOne, OUTPUT);
  pinMode(lightPinTwo, OUTPUT);

  topDisplay.begin();
  bottomDisplay.begin();

  topDisplay.setIntensity(2);
  bottomDisplay.setIntensity(2);

  topDisplay.setTextAlignment(PA_CENTER);
  bottomDisplay.setTextAlignment(PA_CENTER);

  topDisplay.print("Gallium");
  bottomDisplay.displayScroll("The Coolest Metal :D", PA_CENTER, PA_SCROLL_LEFT, 25);
}

void loop() {
  // Update Current State
  if (digitalRead(switchPin) == HIGH && !previouslyActivated) {
    previouslyActivated = true;
    currentState++;

    currentState %= 11;

    switch(currentState) {
      case 0:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("The Coolest Metal :D", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;
      
      case 1:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("Part of the Boron Family", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;
      
      case 2:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("Electron Configuration: 1s^2 2s^2 2p^6 3s^2 3p^6 4s^2 3d^10 4p^1", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;
      
      case 3:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("Two Stable Isotopes: Ga-69 (68.9256) and Ga-71 (70.9247)", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;

      case 4:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("Oxidation Number: +3", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;
      
      case 5:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("Discovered in 1875 by Paul-Emile Lecoq de Boisbaudran (A French Chemist!)", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;

      case 6:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("Everyday Uses: LED Lights, Circuits, Switches, and much more!", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;

      case 7:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("I am going to lose it", PA_CENTER, PA_SCROLL_LEFT, 25);
        break;
      
      case 8:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("AAAAHHHHHHHHH", PA_CENTER, PA_SCROLL_LEFT, 0);
        break;
      
      case 9:
        bottomDisplay.displayClear();
        bottomDisplay.displayScroll("I love Kris Vazquez, Athena Aguilera, Alejandro Hernandez Espinoza, Krisha Rupani, and so many others!", PA_CENTER, PA_SCROLL_LEFT, 0);
        break;
      
      case 10:
        bottomDisplay.displayClear();
        bottomDisplay.setTextAlignment(PA_CENTER);
        startTimer();
    }

  } else if (digitalRead(switchPin) == LOW) {
    previouslyActivated = false;
  }

  // Update Animations
  if (bottomDisplay.displayAnimate() && currentState != 10) {
    bottomDisplay.displayReset();
  }

  // Update LEDs
  if (cycleTimeElapsed <= 500) {
    digitalWrite(lightPinOne, HIGH);
    digitalWrite(lightPinTwo, LOW);

  } else if (cycleTimeElapsed < 1000) {
    digitalWrite(lightPinTwo, HIGH);
    digitalWrite(lightPinOne, LOW);

  } else {
    cycleTimeElapsed = -5;
  }

  cycleTimeElapsed += 5;

  delay(5);
}
