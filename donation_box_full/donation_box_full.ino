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

int fanPin = 12;
int irPin = 1;  // Read data in from IR sensor on analog pin A0
// MP3 Triggers = 1, 2, 3, 4, 6, 7, 8, 9, 11
// TODO: forgot to wire up relay #10!! =
// array index:             0, 1, 2, 3, 4, 5, 6, 7, 8
int arduinoDigitalPins[] = {2, 3, 4, 5, 6, 7, 8, 9};      // corresponds to "Digital" pins on arduino
int mp3Triggers[] =        {1, 2, 3, 4, 6, 7, 8, 9, 11};  // coresponds to "Trigger" pins on robertsonics board
int arduinoDigitalPinsLength = sizeof(arduinoDigitalPins)/sizeof(int);
String wordArray[] = {"THANK YOU!"};
int wordSquareArray[] = {60};

void setup() {
  // enable debugging via serial on 9600
  Serial.begin(9600);
  
  // initialize mp3 pins by setting them to OUTPUT
  for (int i = 0; i < arduinoDigitalPinsLength; i++) {
    pinMode(arduinoDigitalPins[0], OUTPUT);
  }
  
  // initialize fanPin
  pinMode(fanPin, OUTPUT);

  // initialize LED matrix
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(50);
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
}

void scrollText(Adafruit_NeoMatrix matrix) {
  // random(min, max) selects random number from min to (max - 1)
  
  int i = random(0, arduinoDigitalPinsLength);
  int x = matrix.width();
  
  // momentarily raise mp3 trigger pin high to play MP3
  digitalWrite(arduinoDigitalPins[0], HIGH);
  
//  Serial.println("mp3TriggerPinsLength: ");
//  Serial.println(arduinoDigitalPinsLength);
//  Serial.println("array index: ");
//  Serial.println(i);
//  Serial.println("arduino pin: ");
//  Serial.println(arduinoDigitalPins[0]);
//  Serial.println("mp3 trigger: ");
//  Serial.println(mp3Triggers[0]);
//  Serial.println("fanPin: ");
//  Serial.println(fanPin);
//  Serial.println("\n");
  
  delay(500);
  digitalWrite(arduinoDigitalPins[0], LOW);
 
  while (x >= -wordSquareArray[0]) { 
   Serial.println(x); 
    // initialize LED matrix
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(wordArray[0]);
    // move cursor across the LED matrix
    --x;
    
    if (x == -25) {
      // turn the fans on
      digitalWrite(fanPin, HIGH);
      Serial.println("FANS ON");
    }
    
    matrix.show();
    
    delay(100); 
  }
  
  // turn the fans off
    digitalWrite(fanPin, LOW);
    Serial.println("FANS OFF");
//  
}
  


