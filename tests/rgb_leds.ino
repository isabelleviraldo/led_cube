int latchPin = 3;   //Pin connected to ST_CP of 74HC595
int clockPin = 18;  //Pin connected to SH_CP of 74HC595
int dataPin = 19;   ////Pin connected to DS of 74HC595

int numOfRows = 4;
int numOfCols = 12;

byte on = 0xff;
byte off = 0x00;

//each row is a different led on my setup, 1 is r, 2 is g, 3 is b, 4 is white
int colors[4][12] = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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
  //goes through each of the points on the grid, and sends the signal (current sink)
  for (int r = 0; r <= numOfRows; r++){
    for (int c = 0; c <= numOfCols; c++) {
      digitalWrite(latchPin, LOW);
      if (colors[r][c] == 1) {
        shiftOut(dataPin, clockPin, MSBFIRST, off);
      } else {
        shiftOut(dataPin, clockPin, MSBFIRST, on);
      }
      digitalWrite(latchPin, HIGH);
    }
    //delay so they all appear on at once, do 1000 to see slow mo
    delay(2);
  }
}
