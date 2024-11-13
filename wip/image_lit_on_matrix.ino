//**************************************************************//
//  Name    : shiftOutCode, Hello World
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis
//  Date    : 25 Oct, 2006
//  Modified: 23 Mar 2010
//  Version : 2.0
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255
//****************************************************************

#include "ShiftRegisterPWM.h"

int latchPin = 3;   //Pin connected to ST_CP of 74HC595
int clockPin = 18;  //Pin connected to SH_CP of 74HC595
int dataPin = 19;   ////Pin connected to DS of 74HC595

int latchPin2 = 4;
int clockPin2 = 15;
int dataPin2 = 16;

int numOfRows = 6;
int numOfCols = 8;

byte on = 0xff;
byte off = 0x00;

int place = 0;

int rowControl[6][8] = { { 1, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 1, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 1, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 1, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 1, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 1, 0, 0 } };

int image[6][8] = { { 0, 0, 1, 0, 0, 1, 0, 0 },
                    { 0, 0, 1, 0, 0, 1, 0, 0 },
                    { 0, 0, 1, 0, 0, 1, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 1, 0, 0, 0, 0, 0, 0, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1 } };

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
}

void loop() {
  displayImage();
}

void displayImage(){
  for (int r = 0; r <= numOfRows; r++) {
    //controls the rows
    for (int c = 0; c <= numOfRows; c++) {
      digitalWrite(latchPin2, LOW);
      if (rowControl[r][c] == 1) {
        shiftOut(dataPin2, clockPin2, MSBFIRST, on);
      } else {
        shiftOut(dataPin2, clockPin2, MSBFIRST, off);
      }
      digitalWrite(latchPin2, HIGH);
    }
    //controls the cols
    for (int c = 0; c <= numOfCols; c++) {
      digitalWrite(latchPin, LOW);
      if (image[r][c] == 1) {
        shiftOut(dataPin, clockPin, MSBFIRST, off);
      } else {
        shiftOut(dataPin, clockPin, MSBFIRST, on);
      }
      digitalWrite(latchPin, HIGH);
    }
    
    delay(5);
    clear();
    delay(1);

  }

}


int shiftQuadrant(int counter){

  if (counter == 1){
    int quad1[6][8] = { { 1, 1, 1, 1, 0, 0, 0, 0 },
                        { 1, 1, 1, 1, 0, 0, 0, 0 },
                        { 1, 1, 1, 1, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 } };
    assign(quad1);
  } else if (counter == 2){
    int quad2[6][8] = { { 0, 0, 0, 0, 1, 1, 1, 1 },
                        { 0, 0, 0, 0, 1, 1, 1, 1 },
                        { 0, 0, 0, 0, 1, 1, 1, 1 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 } };
    assign(quad2);
  } else if (counter == 3){
    int quad3[6][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 1, 1, 1, 1 },
                        { 0, 0, 0, 0, 1, 1, 1, 1 },
                        { 0, 0, 0, 0, 1, 1, 1, 1 } };
    
    assign(quad3);

  } else if (counter == 4){
    int quad4[6][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 1, 1, 1, 1, 0, 0, 0, 0 },
                        { 1, 1, 1, 1, 0, 0, 0, 0 },
                        { 1, 1, 1, 1, 0, 0, 0, 0 } };
    
    assign(quad4);

    counter == 0;
  }

}

void assign(int vals[6][8]) {
    for (int i = 0; i < numOfRows; i++) {
      for (int j = 0; j < numOfCols; j++){
        image[i][j] = vals[i][j];
      }
    }
}

void clear(){
  for (int r = 0; r <= numOfRows; r++) {
    //controls the rows
    for (int c = 0; c <= numOfRows; c++) {
      digitalWrite(latchPin2, LOW);
      shiftOut(dataPin2, clockPin2, MSBFIRST, off);
      digitalWrite(latchPin2, HIGH);
    }
    for (int c = 0; c <= numOfCols; c++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, on);
      digitalWrite(latchPin, HIGH);
    }
  }
}
