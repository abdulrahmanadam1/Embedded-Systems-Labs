// ______________________ MAIN PROGRAM (.c) ______________________ 
/*
  Abdulrahman Adam
  2076566
  December 3, 2021
  main.c for lab 4 task 2a
  In this task, we display the traffic light function solely through the LCD display
*/
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>
#include "lab4.h"
#include "task2c_functions.h"


int main()
{
  LCD_Init();
  Touch_Init();
  //draw background
  LCD_ColorFill(Color4[15]);
  //draw the traffic light post
  LCD_DrawFilledRect(226,42,60,156,Color4[6]);
  LCD_DrawRect(225,41,61,157,Color4[0]);//outline
  LCD_DrawFilledRect(246,198,20,42,Color4[6]);
  LCD_DrawRect(245,198,21,42,Color4[0]);//outline
  
  //draw where the lights are
  LCD_DrawFilledCircle(256,72,20,Color4[0]);
  LCD_DrawFilledCircle(256,120,20,Color4[0]);
  LCD_DrawFilledCircle(256,168,20,Color4[0]);

  //Draw the virtual buttons
  LCD_DrawFilledCircle(47, 168,20,Color4[0]);//System ON/OFF Button
  LCD_DrawFilledCircle(145,168,20,Color4[0]);//Pedestrian Button
  LCD_SetCursor(45, 164);
  LCD_PrintString("S");
  LCD_SetCursor(143,164);
  LCD_PrintString("P");  
    
  Timer_init0();

  while(1){

  }
 return 0;
}
