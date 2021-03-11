// For RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

volatile int x_step_toggle = 0;
volatile int x_step_count = 0;
void setup()
{
  TCCR1A = 0x00;
  TCCR1B = 0x0a;
  TCCR1C = 0x00;
  OCR1A = 400;
  TIMSK1 = 0x00;

  DDRC |= 0x02 | 0x08 | 0x80;
  DDRL |= 0x08 | 0x01;
  pinMode(Z_ENABLE_PIN, OUTPUT);
  PORTC &= ~0x08;
  PORTL |= 0x01;
}

void loop()
{
  TIMSK1 = 0x02;
}

ISR(TIMER1_COMPA_vect)
{
  if (x_step_toggle == 0)
  {
    x_step_toggle = 1;
    PORTC |= 0x02;
    PORTL |= 0x08;
  }
  else
  {
    x_step_toggle = 0;
    PORTC &= ~0x02;
    PORTL &= ~0x08;
    x_step_count++;
  }
}
