#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // For Arduino Due
#endif

// Matrix: 23W X 7H. Plugged in to Pin 11
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(23, 7, 11,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

int irPin = 1;  // Read data in from IR distance sensor on analog pin A0

void setup() {
  // enable debugging via serial on 9600
  Serial.begin(9600);
  
  // initialize LED matrix
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(matrix.Color(0, 0, 255));
}

void loop() {  
  // 5 = 5volts. 5/1024 = 0.00488...
  float volts = analogRead(irPin)*0.0048828125;
  
  // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
  float distance = 65*pow(volts, -1.10); 
  
  if(distance > 25) {
    matrix.begin();
    scrollText(matrix);  
  }
  //Serial.println(distance);
}

void scrollText(Adafruit_NeoMatrix matrix) {
  while (x >= -36) {    
    // initialize LED matrix
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("THANKS"));
  
    // move cursor across the LED matrix
    --x;
    
    matrix.show();
    
    delay(100); 
  }
}
