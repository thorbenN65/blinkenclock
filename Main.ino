//Hello Libraries
  #include <FastLED.h>

//There are probably a bunch of variables I need to define. So let's do that
//WiFi Variables go here
//NTP server goes here

//PIN for 2812 IO goes here
  #define DATA_PIN 5  //Currently, we listen on D5, which corresponds to 5
  #define NUM_LEDS 112 //This is the total number of LEDs (8*112)
  
  CRGB leds[NUM_LEDS];

//PIN for switch button goes here
 

void setup() {

//We initialise FastLED and add the LEDs to it.
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

//Probably need to get this motherfucker online
//Then need to get a date and time. These values are unlikely to be unstable, unless some really weird shit goes down.
//

//For debugging purposes, we want to listen to the Serial Port
Serial.begin(115200);
delay(5000);  
Serial.println("Hello there");

}

void loop() {
  
  //This is where we want to get initially. Display a pseudo time (before we actually implement a real time clock)
  //In order to do this we will trigger the display binary feature. In our example the time is 15:57, the output should be
  //00001111
  //00111001
  Serial.println("15 und 57");
  displayBinary(15,57,0xFEFEFE,0xCD0000);
  delay(10000);
    Serial.println("300 und 400");
  displayBinary(300,400,0xFEFEFE,0x3B8B68);
  delay(10000);
    Serial.println("0 und 0");
  displayBinary(0,0,0xFEFEFE,0xA93796);
  delay(10000);
    Serial.println("23 und 59");
  displayBinary(23,59,0xFEFEFE,0x00080);
  delay(10000);
    Serial.println("12 und 12");
  displayBinary(12,12,0xFEFEFE,0xA52A2A);
    delay(10000);
      Serial.println("255 und 254");
  displayBinary(255,254,0xFEFEFE,0xFFC0CB);
    delay(10000);
      Serial.println("128 und 64");
  displayBinary(128,64,0xFEFEFE,0xFFFF00);
    delay(10000);
      Serial.println("77 und 88");
  displayBinary(77,88,0xFEFEFE,0x9ACD32);
}



  
void displayBinary(int upperByte, int lowerByte, int baseClr, int pageClr) {

 //This function will process two input values, alongside a colour set on LED1 to give a visual 
 //indication of what page we are looking at. I.e. every page has it's own colour. Additionally
 //we will allow for the digit color to be adjusted

 //Let's do some reality checks. First things first, with 8 bit we can display values from 0-255
 //TODO: Let's round the values first. Then make sure both values are < 256. If the values are
 //larger than 255, we'll just make them 255. As they say in German: was nicht passt wird passend gemacht.

 if (upperByte > 255) {upperByte = 255;}
 if (lowerByte > 255) {lowerByte = 255;}
 Serial.println("Values cut off at 255. Just to confirm, the values are now:");
 Serial.print(upperByte);
 Serial.print(" on the upper line and on the lower ");
 Serial.println(lowerByte);

//Now let's decompose the two ints to binary digit thingies.
//Method 1 using the itob function

char* BinUpperLEDs = itob3(upperByte);
Serial.print("Upper line in binary: ");
Serial.println(BinUpperLEDs);
char* BinLowerLEDs = itob2(lowerByte);
Serial.print("Lower line in binary: ");
Serial.println(BinLowerLEDs);
Serial.println();

//Let's do LEDs

//Let's do the easy bit first and define 08 in the page colour
int basenumber;
for (basenumber = 49; basenumber < 56; ++basenumber) {
  leds[basenumber] = pageClr;
}
  Serial.print("Redering the page with the colour ");
  Serial.println(baseClr);

//Now let's check every digit on line 1
  
 //First things first, for testing, let's rip the array open
 Serial.println("Ripping the array open. Displaying every bit manually for Line ONE:");
 Serial.print(BinUpperLEDs[0]);
 Serial.print(BinUpperLEDs[1]);  
 Serial.print(BinUpperLEDs[2]);
 Serial.print(BinUpperLEDs[3]);
 Serial.print(BinUpperLEDs[4]); 
 Serial.print(BinUpperLEDs[5]);
 Serial.print(BinUpperLEDs[6]);
 Serial.println(BinUpperLEDs[7]);

// Upper LEDs are 7-1
  Serial.println("\n\n Let's determine the status for every dot ofthe upper 7 LEDs");

int LEDlocUp = 7;
while (LEDlocUp > 0)
{
    Serial.print("Sending vars to ShineAUpperDot for LED ");
    Serial.println(LEDlocUp);
    ShineAUpperDot (LEDlocUp, BinUpperLEDs, baseClr);
    LEDlocUp = LEDlocUp-1;
}

/* NOTE TO MYSELF

The upcoming code is so damn repetitive, it should be
fairly easy to get this down to a few lines of code.
I would stick by the principle though, but but in a lot 
more loops and stuffs.

*/
//Let's check every digit on line 2
 //First things first, for testing, let's rip the array open
 Serial.println("Ripping the array open. Displaying every bit manually for Line TWO:");
 Serial.print(BinLowerLEDs[0]);
 Serial.print(BinLowerLEDs[1]);  
 Serial.print(BinLowerLEDs[2]);
 Serial.print(BinLowerLEDs[3]);
 Serial.print(BinLowerLEDs[4]); 
 Serial.print(BinLowerLEDs[5]);
 Serial.print(BinLowerLEDs[6]);
 Serial.println(BinLowerLEDs[7]);

  
  //Lower LEDs are 7-0
Serial.println("\n\n Let's determine the status for every dot of lower 8 LEDs");
int LEDlocLow = 7;
while (LEDlocLow > -1)
{
    Serial.print("Sending vars to ShineALowerDot for LED ");
    Serial.println(LEDlocLow);
    ShineALowerDot (LEDlocLow, BinLowerLEDs, baseClr);
    LEDlocLow = LEDlocLow-1;
}


//We have identified every dot that should be on or off. There's only one thing left to do.
//Launch the fireworks.
//3....
//2....
//1....
//IGNITION

      FastLED.show();
      memset(BinUpperLEDs, 0, sizeof(BinUpperLEDs));
      memset(BinLowerLEDs, 0, sizeof(BinLowerLEDs));
}

/* Essential functions */

   char* itob3(int i3) {
      static char bits3[8] = {'0','0','0','0','0','0','0','0'};
      int bits_index3 = 7;
      while ( i3 > 0 ) {
         bits3[bits_index3--] = (i3 & 1) + '0';
         i3 = ( i3 >> 1);
      }
      return bits3;
   }

      char* itob2(int i2) {
      static char bits2[8] = {'0','0','0','0','0','0','0','0'};
      int bits_index2 = 7;
      while ( i2 > 0 ) {
         bits2[bits_index2--] = (i2 & 1) + '0';
         i2 = ( i2 >> 1);
      }
      return bits2;
   }


/* Coming up are the less verbose versions to light bulbs in the upper and lower lines */

//Much less verbose - a template for shining lower Bulbs
char ShineALowerDot (int BulbID, char* BinLowerLEDs, int baseClr) {
  int LowerBound = (15-BulbID)*7;
  int UpperBound = LowerBound+7;
  int DotId = 16 - BulbID;
  
  if (BinLowerLEDs[BulbID] == '1') {
    int LedValue;
    for (LedValue = LowerBound; LedValue < UpperBound; ++LedValue) {
      leds[LedValue] = baseClr;
    }
    Serial.print("Dot ");
    Serial.print (BulbID);
    Serial.println(" is on.");

  }
  else{
    int LedValue;
    for (LedValue = LowerBound; LedValue < UpperBound; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    } 
    Serial.print("Dot ");
    Serial.print (BulbID);
    Serial.println(" is off.");   
  }
}

//Upper line, for every x - Lower bound = (7-x)*7, upper bound (7-x)*7+7
char ShineAUpperDot (int BulbID, char* BinLowerLEDs, int baseClr) {
  int LowerBound = (7-BulbID)*7;
  int UpperBound = LowerBound+7;
  int DotId = 16 - BulbID;
  
  if (BinLowerLEDs[BulbID] == '1') {
    int LedValue;
    for (LedValue = LowerBound; LedValue < UpperBound; ++LedValue) {
      leds[LedValue] = baseClr;
    }
    Serial.print("Dot ");
    Serial.print (BulbID);
    Serial.println(" is on.");

  }
  else{
    int LedValue;
    for (LedValue = LowerBound; LedValue < UpperBound; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    } 
    Serial.print("Dot ");
    Serial.print (BulbID);
    Serial.println(" is off.");   
  }
}