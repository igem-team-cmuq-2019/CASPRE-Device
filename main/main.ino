#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial BT(10, 11); // RX, TX

int ledpin = 9;
int BluetoothData;
int funButton = 6;
int florenceSensor = A0;
int val = 0;
float normVal = 0.0;
float trialVals[3];
bool buttonStart = false;

float threshold = 3.45;

String buffer = "";

void setup() {
  BT.begin(9600);

  pinMode(ledpin, OUTPUT);
  pinMode(funButton, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    BT.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();

  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("CASPRE - 2019");
  display.setCursor(0, 10);
  display.print("Press Button to Start");
  display.display();
  BT.println("CASPRE-INIT");
}

void loop() {
  buffer = "";
  //Wait until button press to continue
  if (digitalRead(funButton) == LOW) {
    BT.println("CASPRE-START");
    for(int i = 0; i < 3; i++) {
        // Excite fluorescent tags
        digitalWrite(ledpin, 1);
        delay(500);
        val = analogRead(florenceSensor);
        delay(100);
        digitalWrite(ledpin, 0);
        delay(100);
        trialVals[i] = (1024.0/(float)val);
    }
    // Get average of 3 trial runs in O(1) time
    normVal = (trialVals[0] + trialVals[1] + trialVals[2])/3.0;
        
    if (normVal > threshold)
      buffer += "Pos: ";
    else 
      buffer += "Neg: ";
      
    buffer += String(normVal, 2);

    BT.println("CASPRE-END");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print(buffer);
    display.display();
    BT.println(buffer);

    display.clearDisplay();
    BT.overflow();
    delay(100);
  }
}
