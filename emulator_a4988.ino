#define INPUT_STEP 2
#define INPUT_DIRECTION 3
#define STEPPERa1 4
#define STEPPERa2 5
#define STEPPERb1 6
#define STEPPERb2 7
#define LED 8

#include <AccelStepper.h>

AccelStepper motor1(4, STEPPERa1, STEPPERa2, STEPPERb1, STEPPERb2);

void setup()
{
  pinMode( INPUT_STEP, INPUT );
  pinMode( INPUT_DIRECTION, INPUT );
  pinMode(LED, OUTPUT);
}

void loop()
{
  digitalWrite(LED, digitalRead(LED) ^ HIGH);
  delay(2000);
}