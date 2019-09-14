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
 
 //Let's build an array for the LED values. Each primary element contains all values of all LEDs on one chip.
 //Careful: this array may be obsolete. Also: it starts at 1, when it should really start at 0.

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

//We initialise FastLED and add the LEDs to it.
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

//Probably need to get this motherfucker online
//Then need to get a date and time. These values are unlikely to be unstable, unless some really weird shit goes down.
//

//For debugging purposes, we want to listen to the Serial Port
Serial.begin(115200);
delay(25);  
Serial.println("Hello there");

}

void loop() {
  
  //This is where we want to get initially. Display a pseudo time (before we actually implement a real time clock)
  //In order to do this we will trigger the display binary feature. In our example the time is 15:57, the output should be
  //00001111
  //00111001
  delay(10000);
  Serial.println("15 und 57");
  displayBinary(15,57,0xFEFEFE,0xCD0000);
  delay(10000);
    Serial.println("300 und 400");
  displayBinary(300,400,0xFEFEFE,0xCD0000);
  delay(10000);
    Serial.println("0 und 0");
  displayBinary(0,0,0xFEFEFE,0xCD0000);
  delay(10000);
    Serial.println("23 und 59");
  displayBinary(23,59,0xFEFEFE,0xCD0000);
  delay(10000);
    Serial.println("12 und 12");
  displayBinary(12,12,0xFEFEFE,0xCD0000);
    delay(10000);
      Serial.println("255 und 254");
  displayBinary(255,254,0xFEFEFE,0xCD0000);
    delay(10000);
      Serial.println("128 und 64");
  displayBinary(128,64,0xFEFEFE,0xCD0000);
    delay(10000);
      Serial.println("77 und 88");
  displayBinary(77,88,0xFEFEFE,0xCD0000);
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
  
void displayBinary(int upperByte, int lowerByte, int baseClr, int pageClr) {

 //This function will process two input values, alongside a colour set on 01 to give a visual 
 //indication of what page we are looking at. I.e. every page has it's own colour.
 //Debug indicator: function starts running
 Serial.println("displayBinary was triggered");

 //Let's do some reality checks. First things first, with 8 bit we can display values from 0-255
 //TODO: Let's round the values first. Then make sure both values are < 256. If the values are
 //larger than 255, we'll just make them 255. As they say in German: was nicht passt wird passend gemacht.

 if (upperByte > 255) {upperByte = 255;}
 if (lowerByte > 255) {lowerByte = 255;}
 Serial.println("Values cut off at 255");
 Serial.println(upperByte);
 Serial.println(lowerByte);
 Serial.println();

//Actually, we don't even need to round. They are integers for a reason. Let's just check what we have for debut
Serial.print("Upper line: ");
Serial.print(upperByte);
Serial.print(" - Lower line: ");
Serial.println(lowerByte);
Serial.println();

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

//Show the page colour, then chill for a second.
      FastLED.show();
      delay(1000);


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
  
  //01
  Serial.println("\n\n Let's determine the status for every dot of 7 LEDs");
  if (BinUpperLEDs[7] == '1') {
    int LedValue;
    for (LedValue = 0; LedValue < 7; ++LedValue) {
      leds[LedValue] = baseClr;
    }
    Serial.println("Dot 1 is on.");

  }
  else{
    int LedValue;
    for (LedValue = 0; LedValue < 7; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    } 
    Serial.println("Dot 1 is off.");   
  }
      //02
  if (BinUpperLEDs[6] == '1') {
    int LedValue;
    for (LedValue = 7; LedValue < 14; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 2 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 7; LedValue < 14; ++LedValue) {
      leds[LedValue] = 0x000000;
    }
    Serial.println("Dot 2 is off.");    
  }

  if (BinUpperLEDs[5] == '1') {
    int LedValue;
    for (LedValue = 14; LedValue < 21; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 3 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 14; LedValue < 21; ++LedValue) {
      leds[LedValue] = 0x000000;
    }
    Serial.println("Dot 3 is off.");    
  }

    if (BinUpperLEDs[4] == '1') {
    int LedValue;
    for (LedValue = 21; LedValue < 28; ++LedValue) {
      leds[LedValue] = baseClr;
    }
    Serial.println("Dot 4 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 21; LedValue < 28; ++LedValue) {
      leds[LedValue] = 0x000000;
    }
    Serial.println("Dot 4 is off.");
  }

    if (BinUpperLEDs[3] == '1') {
    int LedValue;
    for (LedValue = 28; LedValue < 35; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 5 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 28; LedValue < 35; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    }
    Serial.println("Dot 5 is off.");    
  }

    if (BinUpperLEDs[2] == '1') {
    int LedValue;
    for (LedValue = 35; LedValue < 42; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 6 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 35; LedValue < 42; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    } 
    Serial.println("Dot 6 is off.");   
  }

    if (BinUpperLEDs[1] == '1') {
    int LedValue;
    for (LedValue = 42; LedValue < 49; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 7 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 42; LedValue < 49; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    }
    Serial.println("Dot 7 is off.");    
  }
  Serial.println("Upper Line done\nCAUTION: UpperLine has only 7 LEDs\n");


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

  
  //09
  if (BinLowerLEDs[7] == '1') {
    int LedValue;
    for (LedValue = 56; LedValue < 63; ++LedValue) {
      leds[LedValue] = baseClr;
    }
    Serial.println("Dot 9 is on.");

  }
  else{
    int LedValue;
    for (LedValue = 56; LedValue < 63; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    } 
    Serial.println("Dot 9 is off.");   
  }
      //10
  if (BinLowerLEDs[6] == '1') {
    int LedValue;
    for (LedValue = 63; LedValue < 70; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 10 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 63; LedValue < 70; ++LedValue) {
      leds[LedValue] = 0x000000;
    }
    Serial.println("Dot 10 is off.");    
  }

  if (BinLowerLEDs[5] == '1') {
    int LedValue;
    for (LedValue = 70; LedValue < 77; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 11 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 70; LedValue < 77; ++LedValue) {
      leds[LedValue] = 0x000000;
    }
    Serial.println("Dot 11 is off.");    
  }

    if (BinLowerLEDs[4] == '1') {
    int LedValue;
    for (LedValue = 77; LedValue < 84; ++LedValue) {
      leds[LedValue] = baseClr;
    }
    Serial.println("Dot 12 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 77; LedValue < 84; ++LedValue) {
      leds[LedValue] = 0x000000;
    }
    Serial.println("Dot 12 is off.");
  }

    if (BinLowerLEDs[3] == '1') {
    int LedValue;
    for (LedValue = 84; LedValue < 91; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 13 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 84; LedValue < 91; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    }
    Serial.println("Dot 13 is off.");    
  }

    if (BinLowerLEDs[2] == '1') {
    int LedValue;
    for (LedValue = 91; LedValue < 98; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 14 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 91; LedValue < 98; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    } 
    Serial.println("Dot 14 is off.");   
  }

    if (BinLowerLEDs[1] == '1') {
    int LedValue;
    for (LedValue = 98; LedValue < 105; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 15 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 98; LedValue < 105; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    }
    Serial.println("Dot 15 is off.");    
  }

      if (BinLowerLEDs[0] == '1') {
    int LedValue;
    for (LedValue = 105; LedValue < 112; ++LedValue) {
      leds[LedValue] = baseClr;
      
    }
    Serial.println("Dot 16 is on.");
  }
  else{
    int LedValue;
    for (LedValue = 105; LedValue < 112; ++LedValue) {
      leds[LedValue] = 0x000000;
      
    }
    Serial.println("Dot 16 is off.");    
  }



//We have identified every dot that should be on or off. There's only one thing left to do.
//Launch the fireworks.
//3....
//2....
//1....
//IGNITION

      FastLED.show();
}



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