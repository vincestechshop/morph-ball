/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.

  To upload to your Gemma or Trinket:
  1) Select the proper board from the Tools->Board Menu
  2) Select USBtinyISP from the Tools->Programmer
  3) Plug in the Gemma/Trinket, make sure you see the green LED lit
  4) For windows, install the USBtiny drivers
  5) Press the button on the Gemma/Trinket - verify you see
     the red LED pulse. This means it is ready to receive data
  6) Click the upload button above within 10 seconds
*/
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEO_DIGITAL_PIN            1
// Analog pin numbering can be different on Trinket. analogRead(1) is A1, pin 2 as marked on the trinket
// Analog 1/Digital 2
// Analog 3/Digital 3
// Analog 4/Digital 4
#define SHAKE_SENSOR   1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      6

#define DEMO        0
#define RED_PULSE   1
#define GREEN_PULSE 2
#define BLUE_PULSE  3
#define number_of_modes 4

int color = 0;
int mode = RED_PULSE; // Tracks current light mode

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEO_DIGITAL_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay for half a second

int last_mode_change = millis();

// the setup routine runs once when you press reset:
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  // Set Digital Pin 3 high
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  mode = check_shake_sensor(mode);

  if(mode == DEMO) {
    // demo red then green then blue
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();
    }
    for(int checkloop = 0; checkloop < 20; checkloop++) {
      delay(50);
      mode = check_shake_sensor(mode);
    }

    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();
    }
    for(int checkloop = 0; checkloop < 20; checkloop++) {
      delay(50);
      mode = check_shake_sensor(mode);
    }

    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,255));
      pixels.show();
    }
    for(int checkloop = 0; checkloop < 20; checkloop++) {
      delay(50);
      mode = check_shake_sensor(mode);
    }
  }

  if(mode == RED_PULSE) {
    for(int brightness = 50;brightness <= 255;brightness += 5) {
      for(int i = 0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(brightness, 0, 0));
        pixels.show();
      }
      delay(20);
      mode = check_shake_sensor(mode);
    }

    for(int brightness = 255;brightness >= 50;brightness -= 5) {
      for(int i = 0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(brightness, 0, 0));
        pixels.show();
      }
      delay(20);
      mode = check_shake_sensor(mode);
    }
  }

  if(mode == GREEN_PULSE) {
    for(int brightness = 50;brightness <= 255;brightness += 5) {
      for(int i = 0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(0, brightness, 0));
        pixels.show();
      }
      delay(20);
      mode = check_shake_sensor(mode);
    }

    for(int brightness = 255;brightness >= 50;brightness -= 5) {
      for(int i = 0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(0, brightness, 0));
        pixels.show();
      }
      delay(20);
      mode = check_shake_sensor(mode);
    }
  }

  if(mode == BLUE_PULSE) {
    for(int brightness = 50;brightness <= 255;brightness += 5) {
      for(int i = 0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, brightness));
        pixels.show();
      }
      delay(20);
      mode = check_shake_sensor(mode);
    }

    for(int brightness = 255;brightness >= 50;brightness -= 5) {
      for(int i = 0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, brightness));
        pixels.show();
      }
      delay(20);
      mode = check_shake_sensor(mode);
    }
  }
}

int check_shake_sensor(int mode) {

  int reading = analogRead(SHAKE_SENSOR);

  // If the voltage is high enough on the analog pin and it has been over a second since the last change (debounce vibration sensor)
  // REDUCE VIBRATION SENSITIVITY BY INCREASING THE READING VALUE BELOW
  if(reading > 820 && millis() - last_mode_change > 1000) {
    // flash white to indicate mode change
    for(int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.show();
    }
    delay(100);
    last_mode_change = millis();
    mode++;

    if(mode == number_of_modes) {
      mode = 0;
    }

    return mode;
  }
}
