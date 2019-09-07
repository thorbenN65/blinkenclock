//Hello Libraries
#include <FastLED.h>

//There are probably a bunch of variables I need to define. So let's do that
//WiFi Variables go here
//NTP server goes here
//PIN for 2812 IO goes here
#define DATA_PIN 5
#define NUM_LEDS 112
CRGB leds[NUM_LEDS];
//PIN for switch button goes here
 //Let's build an array for the LED values. Each primary element contains all values of all LEDs on one chip.

 int ledGrid[16][7] ={

  {106,107,108,109,110,111,112},  //01
  {99,100,101,102,103,104,105},   //02
  {92,93,94,95,95,97,98},         //03
  {85,86,87,88,89,90,91},         //04
  {78,79,80,81,82,83,84},         //05
  {71,72,73,74,75,76,77},         //06
  {64,65,66,67,68,69,70},         //07
  {57,58,59,60,61,62,63},         //08
  {50,51,52,53,54,55,56},         //09
  {43,44,45,46,47,48,49},         //10
  {36,37,38,39,40,41,42},         //12
  {29,30,31,32,33,34,35},         //13
  {22,23,24,25,26,27,28},         //14
  {15,16,17,18,19,20,21},         //15
  {8,9,10,11,12,13,14},           //16
  {1,2,3,4,5,6,7}                 //16

 };

void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // put your setup code here, to run once:
  
  //Probably need to get this motherfucker online
  //Then need to get a date and time. These values are unlikely to be unstable, unless some really weird shit goes down.
  //

Serial.begin(9600);
delay(25);  
Serial.println("Hello there");
}

void loop() {
  // put your main code here, to run repeatedly:


  
  //This is where we want to get initially. Display a pseudo time (before we actually implement a real time clock)
  //In order to do this we will trigger the display binary feature. In our example the time is 15:57, the output should be
  //00001111
  //00111001
  displayBinary("00001111","00111001",0xFEFEFE,0xCD0000);
  delay(3000);
}


/* Naming convention for the LED fields
 *  
 *  +++++++++++++++++++++++++++++++++++++++++++
 *  ++ 08 + 07 + 06 + 05 + 04 + 03 + 02 + 01 ++
 *  +++++++++++++++++++++++++++++++++++++++++++
 *  ++ 16 + 15 + 14 + 13 + 12 + 11 + 10 + 09 ++
 *  +++++++++++++++++++++++++++++++++++++++++++
 *  
 *  Each Neopixel consists of 7 lights. So the pixel range is 
 *  FIELD_NUMBER-1 (
 */
  
void displayBinary(char upperBit[8], char lowerBit[0], int baseClr, int pageClr) {

 //This function will process two input values, alongside a colour set on 01 to give a visual indication of what page we are looking at. I.e. every page has it's own colour.
 
 //Let's do some reality checks. First things first, with 8 bit we can display values from 0-255
 //TODO: Let's round the values first. Then make sure both values are < 256.

//Now let's decompose the two ints to binary digit thingies.

char Line1 = upperBit;

Serial.println("Upper byte:");
Serial.println(Line1);
char Line2 = lowerBit;
Serial.println("Lower byte:");
Serial.println(Line2);

//Let's do LEDs

//Let's do the easy bit first and define 08 in the page colour
int basenumber;
for (basenumber = 49; basenumber < 56; ++basenumber) {
  leds[basenumber] = pageClr;
}
      //leds[8] = baseClr;
      //leds[45] = pageClr;
      //leds[102] = pageClr;
      FastLED.show();
      delay(1000);


      //Now let's check every digit on line 1
      //01
  if (Line1[7] = 1) {
    int LedValue;
    for (LedValue = 0; LedValue < 7; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 0; LedValue < 7; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }
      //02
  if (Line1[6] = 1) {
    int LedValue;
    for (LedValue = 7; LedValue < 14; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 7; LedValue < 14; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }

  if (Line1[5] = 1) {
    int LedValue;
    for (LedValue = 14; LedValue < 21; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 14; LedValue < 21; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }

    if (Line1[4] = 1) {
    int LedValue;
    for (LedValue = 21; LedValue < 28; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 21; LedValue < 28; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }

    if (Line1[3] = 1) {
    int LedValue;
    for (LedValue = 28; LedValue < 35; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 28; LedValue < 35; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }

    if (Line1[2] = 1) {
    int LedValue;
    for (LedValue = 35; LedValue < 42; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 35; LedValue < 42; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }

    if (Line1[1] = 1) {
    int LedValue;
    for (LedValue = 42; LedValue < 49; ++LedValue) {
      leds[LedValue] = baseClr;
    }
  }
  else{
    int LedValue;
    for (LedValue = 42; LedValue < 49; ++LedValue) {
      leds[LedValue] = 0x000000;
    }    
  }
  
      //Let's check every digit on line 2
      FastLED.show();
}



   char* itob(int i) {
      static char bits[8] = {'0','0','0','0','0','0','0','0'};
      int bits_index = 7;
      while ( i > 0 ) {
         bits[bits_index--] = (i & 1) + '0';
         i = ( i >> 1);
      }
      return bits;
   }