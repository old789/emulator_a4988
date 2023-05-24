#define USE_SERIAL

// pins 
#define INPUT_STEP 2
#define INPUT_DIRECTION 3
#define STEPPERa1 4
#define STEPPERa2 5
#define STEPPERb1 6
#define STEPPERb2 7
#define LED 8
#define LED_BUILTIN 14

// motor
#define STEPS 100 //  360 / 3.6
#define RPM 30
#define STEPS_FORWARD 3
#define STEPS_BACK -1 * STEPS_FORWARD

#define   NOP __asm__ __volatile__ ("nop\n\t")
 
#include <Stepper.h>

uint8_t state = LOW;
uint16_t tick = 0;

Stepper motor(STEPS, STEPPERa1, STEPPERa2, STEPPERb1, STEPPERb2);

void setup() {
  pinMode( INPUT_STEP, INPUT );
  pinMode( INPUT_DIRECTION, INPUT );
  pinMode( LED, OUTPUT );
  pinMode(LED_BUILTIN, OUTPUT);
  motor.setSpeed( RPM );
#ifdef USE_SERIAL
  Serial.begin(9600);
  delay(2000);
  Serial.println("Booted");
#endif
}

void loop() {
  int8_t d = 1;
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
  d = digitalRead( INPUT_DIRECTION ) == LOW ? STEPS_BACK : STEPS_FORWARD;
#ifdef USE_SERIAL
  Serial.print("Step(s):");
  Serial.println(d);
#endif
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
