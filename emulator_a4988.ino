#define INPUT_STEP 2
#define INPUT_DIRECTION 3
#define STEPPERa1 4
#define STEPPERa2 5
#define STEPPERb1 6
#define STEPPERb2 7
#define LED 8

#define STEPS 100 //  360 / 3.6
#define RPM 30

#define   NOP __asm__ __volatile__ ("nop\n\t")
 
#include <Stepper.h>

uint8_t state = LOW;

Stepper motor(STEPS, STEPPERa1, STEPPERa2, STEPPERb1, STEPPERb2);

void setup() {
  pinMode( INPUT_STEP, INPUT );
  pinMode( INPUT_DIRECTION, INPUT );
  pinMode( LED, OUTPUT );
  motor.setSpeed( RPM );
}

void loop() {
  uint8_t d = 1;
  if ( digitalRead( INPUT_STEP ) == LOW ){
    if ( state == HIGH ) {
      state = LOW;
      digitalWrite( LED, LOW );
    }
    nop5();
    return;
  }
  if ( state == HIGH ) {
    return;
  }
  digitalWrite( LED, HIGH );
  state = HIGH;
  d = digitalRead( INPUT_DIRECTION ) == LOW ? -1 : 1;
  motor.step(d);
}

void nop5() {
  NOP;
  NOP;
  NOP;
  NOP;
  NOP;
  NOP;  
}
