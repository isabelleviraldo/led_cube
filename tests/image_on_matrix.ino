//shift registers 1 and 2
int latchPin = 3;
int clockPin = 18;
int dataPin = 19;
int latchPin2 = 4;
int clockPin2 = 15;
int dataPin2 = 16;

int numOfRows = 6;
int numOfCols = 8;

byte on = 0xff;
byte off = 0x00;

int place = 0;

int rowControl[6][6] = { { 1, 0, 0, 0, 0, 0 },
                         { 0, 1, 0, 0, 0, 0 },
                         { 0, 0, 1, 0, 0, 0 },
                         { 0, 0, 0, 1, 0, 0 },
                         { 0, 0, 0, 0, 1, 0 },
                         { 0, 0, 0, 0, 0, 1 } };

//note, matrix leds are wired ground, while the rows are wired power, so if image[r][c] == 1, we actually do off
//edit after edit, i think above is actually incorrect, its been a minute, so test to double check ig
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
    //controls the rows of matrix
    for (int c = 0; c <= 6; c++) {
      digitalWrite(latchPin2, LOW);
      if (rowControl[r][c] == 1) {
        shiftOut(dataPin2, clockPin2, MSBFIRST, on);
      } else {
        shiftOut(dataPin2, clockPin2, MSBFIRST, off);
      }
      digitalWrite(latchPin2, HIGH);
    }
    //controls the cols of matrix
    for (int c = 0; c <= numOfCols; c++) {
      digitalWrite(latchPin, LOW);
      if (image[r][c] == 1) {
        shiftOut(dataPin, clockPin, MSBFIRST, off);
      } else {
        shiftOut(dataPin, clockPin, MSBFIRST, on);
      }
      digitalWrite(latchPin, HIGH);
    }
    
    delay(2);
  }
}

void clear(){
  for (int r = 0; r <= numOfRows; r++) {
    //controls the rows of matrix
    for (int c = 0; c <= 6; c++) {
      digitalWrite(latchPin2, LOW);
      shiftOut(dataPin2, clockPin2, MSBFIRST, off);
      digitalWrite(latchPin2, HIGH);
    }
    //controls the cols of matrix
    for (int c = 0; c <= numOfCols; c++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, on);
      digitalWrite(latchPin, HIGH);
    }
  }
}
