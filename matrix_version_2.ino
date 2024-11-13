
#include "ShiftRegisterPWM.h"
#define ShiftRegisterPWM_LATCH_PORT PORTD
#define ShiftRegisterPWM_LATCH_MASK 3
#define ShiftRegisterPWM_CLOCK_PORT PORTC
#define ShiftRegisterPWM_CLOCK_MASK 4
#define ShiftRegisterPWM_DATA_PORT PORTC
#define ShiftRegisterPWM_DATA_MASK 5


int latchPin = 3;   //Pin connected to ST_CP of 74HC595
int clockPin = 18;  //Pin connected to SH_CP of 74HC595
int dataPin = 19;   ////Pin connected to DS of 74HC595

int numOfRows = 8;
int numOfCols = 12;

byte on = 0xff;
byte off = 0x00;

int colors[8][12] = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 } };

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{
  ShiftRegisterPWM sr(1, 255);

  sr.interrupt(ShiftRegisterPWM::UpdateFrequency::Fast);
  while (true) {
    for (uint8_t i = 0; i < 8; i++) {
      uint8_t val = (uint8_t)(((float)sin(millis() / 150.0 + i / 8.0 * 2.0 * PI) + 1) * 128);
      sr.set(i, val);
    }
  }
}