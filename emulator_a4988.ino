#define USE_SERIAL

// pins 
#define INPUT_STEP 2
#define INPUT_DIRECTION 3
#define STEPPERa1 4
#define STEPPERa2 5
#define STEPPERb1 6
#define STEPPERb2 7
#define LED 8
// Hack for Arduino pro micro
#define LED_BUILTIN 17

// motor
#define STEPS 100 //  360 / 3.6
#define RPM 30
#define STEPS_FORWARD 3
#define STEPS_BACK -1 * STEPS_FORWARD

#define   NOP __asm__ __volatile__ ("nop\n\t")

#include <avr/wdt.h>
#include <Stepper.h>

uint8_t state = LOW;
unsigned long prev_timestamp = 0;
uint16_t tick_led = 0;
uint16_t tick_wdt = 0;

Stepper motor(STEPS, STEPPERa1, STEPPERa2, STEPPERb1, STEPPERb2);

/* 
 * без скидання MCUSR буде bootloop після спрацювання watchdog після включення живлення на чіпах PA & PB
 * що цікаво, після скидання сигналом RESET або у випадку чіпів P, такого ефекту нема.
 * Взагалі-то досить код із цієї функції помістити в функцію setup, але мануал на чіп радить так.
 */
 
void clr_mcusr(void) __attribute__((naked)) __attribute__((section(".init3")));

void clr_mcusr(void){
  MCUSR = 0;
  wdt_disable();
}

void setup() {
  pinMode( INPUT_STEP, INPUT );
  pinMode( INPUT_DIRECTION, INPUT );
  pinMode( LED, OUTPUT );
  pinMode(LED_BUILTIN, OUTPUT);
  motor.setSpeed( RPM );
# ifdef USE_SERIAL
  Serial.begin(9600);
  delay(2000);
  Serial.println("Booted");
# endif
  wdt_enable (WDTO_250MS);
}

void loop() {
  int8_t d = 1;
  heartbeat();
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
# ifdef USE_SERIAL
  Serial.print("Step(s):");
  Serial.println(d);
# endif
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

void heartbeat() {
unsigned long timestamp = millis();
uint16_t delta = 0; 

  if ( timestamp < prev_timestamp ) {
    delta = (uint16_t)( 0xffffffff - prev_timestamp + timestamp );
  }else{
    delta = (uint16_t)( timestamp - prev_timestamp );
  }
  prev_timestamp = timestamp;
  tick_led += delta;
  tick_wdt += delta;
  
  if ( tick_wdt > 75 ) { 
    wdt_reset();
    tick_wdt = 0;
  }
  
  if ( tick_led > 1000 ) {
#   ifdef USE_SERIAL
    Serial.println("Tick");
#   endif
    tick_led = 0;
    digitalWrite( LED_BUILTIN, digitalRead( LED_BUILTIN ) ^ HIGH );
  }
  
}
