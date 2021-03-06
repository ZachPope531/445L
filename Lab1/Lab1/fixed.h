#include <stdint.h>
// filename ******** fixed.h ************** 
// possible header file for Lab 1 Spring 2018
// feel free to change the specific syntax of your system
// Zachary Pope and Ali Kedwaii
// 01/29/2018

/****************ST7735_sDecOut2***************
 converts fixed point number to LCD
 format signed 32-bit with resolution 0.01
 range -99.99 to +99.99
 Inputs:  signed 32-bit integer part of fixed-point number
 Outputs: none
 send exactly 6 characters to the LCD 
Parameter LCD display
 12345    " **.**"
  2345    " 23.45"  
 -8100    "-81.00"
  -102    " -1.02" 
    31    "  0.31" 
-12345    "-**.**"
First check if n is outside acceptable range, and display error value if so
Initiallize output string with decimal in proper spot
Initiallize buffer string
(Make number positive if negative, to avoid dealing w/ 2's comp)
Convert digits to ASCII in buffer
Move buffer chars to output array
Add negative symbol if negative
Output
 */ 
void ST7735_sDecOut2(int32_t n);


/**************ST7735_uBinOut6***************
 unsigned 32-bit binary fixed-point with a resolution of 1/64. 
 The full-scale range is from 0 to 999.99. 
 If the integer part is larger than 63999, it signifies an error. 
 The ST7735_uBinOut6 function takes an unsigned 32-bit integer part 
 of the binary fixed-point number and outputs the fixed-point value on the LCD
 Inputs:  unsigned 32-bit integer part of binary fixed-point number
 Outputs: none
 send exactly 6 characters to the LCD 
Parameter LCD display
     0	  "  0.00"
     1	  "  0.01"
    16    "  0.25"
    25	  "  0.39"
   125	  "  1.95"
   128	  "  2.00"
  1250	  " 19.53"
  7500	  "117.19"
 63999	  "999.99"
 64000	  "***.**"
Check if n is outside acceptable range, and display error val if so
Initialize output and buffer strings
Multiply n by 100, then divide by 64
Convert digits to ASCII in buffer
Move buffer chars to output array
Output
*/
void ST7735_uBinOut6(uint32_t n); 

/**************ST7735_XYplotInit***************
 Specify the X and Y axes for an x-y scatter plot
 Draw the title and clear the plot area
 Inputs:  title  ASCII string to label the plot, null-termination
          minX   smallest X data value allowed, resolution= 0.001
          maxX   largest X data value allowed, resolution= 0.001
          minY   smallest Y data value allowed, resolution= 0.001
          maxY   largest Y data value allowed, resolution= 0.001
 Outputs: none
 assumes minX < maxX, and miny < maxY
 
Resets the cursor, applies the title, fills white plot, and sets
global variables for minum and maximum values for use in ST7735_XYplot
*/
void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY);

/**************ST7735_XYplot***************
 Plot an array of (x,y) data
 Inputs:  num    number of data points in the two arrays
          bufX   array of 32-bit fixed-point data, resolution= 0.001
          bufY   array of 32-bit fixed-point data, resolution= 0.001
 Outputs: none
 assumes ST7735_XYplotInit has been previously called
 neglect any points outside the minX maxY minY maxY bounds
 
 First takes 32-bit fixed-point input and checks whether they're in the range set by ST7735_XYplotInit
 Then loops through drawing pixels for each point in the buffers
 Reflects Y-coordinates over the X-axis of the plot as the screen is "upside down"
 Shifts drawn pixels 36 pixels down and 4 pixels to the right to fit plot area
 Maps values taken from the input to a scale that will fit the plot area, eg. 120x120
 Mapping function based off of Arduino map()
*/
void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[]);



