// ______________________ MAIN PROGRAM (.c) ______________________ 
/*
  Abdulrahman Adam
  2076566
  December 3, 2021
  main.c for lab 4 task 2b
  In this task, we display the traffic light function solely through the LCD display
  using RTOS instead of Bare-Metal programming
*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>
#include "task.h"
// Include the LCD driver's header file, the PLL driver's header file,
// and your own header file here.

// After skimming through the entire file,
// you might want to add some FSM states here.


// Hint:
//
// The following global variables are flags you may want to use
int pedestrian_status = 0;
int onoff_status = 0;


// Below are function prototypes for our RTOS task.
// You should not change the function declerations.
// However, you are allowed to add more helper functions
// as needed.

// Task function that checks the state of the virtual pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the virtual pedestrian button for 2 seconds,
// it will set the global flag indicating the virtual pedestrian button
// has been pressed.
void Pedestrian(void *p);

// Task function that checks the state of the virtual onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the virtual traffic light has been
// lighting on. It will update the state of the traffic light system
// every 5 seconds or once there's virtual button input.
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}


// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by initialize the display and touch
  // functionalities of your SSD2119 touch display assembly. You may
  // also want to initialize (draw) your virtual buttons here.
  // Moreover, initialize the PLL to set the system clock to 60 MHz.
  LCD_Init();
  Touch_Init();

  LCD_ColorFill(Color4[15]);
  LCD_DrawFilledRect(226,42,60,156,Color4[6]);
  LCD_DrawRect(225,41,61,157,Color4[0]);//outline
  LCD_DrawFilledRect(246,198,20,42,Color4[6]);
  LCD_DrawRect(245,198,21,42,Color4[0]);//outline
  
  LCD_DrawFilledCircle(256,72,20, Color4[0]);
  LCD_DrawFilledCircle(256,120,20,Color4[0]);
  LCD_DrawFilledCircle(256,168,20,Color4[0]);
  
  LCD_DrawFilledCircle(47, 168,20,Color4[0]);//System ON/OFF Button
  LCD_DrawFilledCircle(145,168,20,Color4[0]);//Pedestrian Button
  LCD_SetCursor(45, 164);
  LCD_PrintString("S");
  LCD_SetCursor(143,164);
  LCD_PrintString("P");  
  // STEP 2
  //
  // The code below creates three tasks.
  // Your task here is to assign priorities to the tasks.
  //
  // Think about which task(s) should be given the highest
  // priority and which should be given lower. It is possible to assign
  // the same priority to all the tasks, however.
  //
  // Priorities are in range: [0, configMAX_PRIORITIES - 1], where
  // configMAX_PRIORITIES - 1 corresponds to the highest priority and
  // 0 corresponds to the lowest priority.
  // You can find configMAX_PRIORITIES defined in the file called FreeRTOSConfig.h
  // under the freertos_demo directory.
  //
  // You should not create more tasks. However, you are allowed to add as many
  // helper functions as you want.
  // xTaskCreate(Function Name,
  //             Descriptive Task Name,
  //             Stack Depth,
  //             Task Function Parameter,
  //             Priority,
  //             Task Handle);
  xTaskCreate(StartStop,(const char *)"StartStopButton", 1024, NULL, 2, NULL);//priority 2
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, 2, NULL);//priority 2
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, 1, NULL);//priority 1

  // Start the scheduler. This should not return.
  // The scheduler will do the scheduling and switch between
  // different tasks for you.
  // Refer to the lecture slides and RTOS documentation
  // page for more details about task scheduling and context switching.
  //
  // One important concept for context switching and task scheduling
  // is preemption. Think about what the terminology preemptive and
  // non-preemptive mean.
  //
  // Hint: Non-preemptive scheduling will allow other tasks to be scheduled
  // after the current task has entered the "waiting state". That is, in our context,
  // the current task will keep running until it reaches vTaskDelay
  // (you'll see this in task functions).
  //
  // You can find in FreeRTOSConfig.h the setting of preemption
  // for the RTOS. Feel free to change this setting as needed.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}
}

void StartStop(void *p) {
  // Hint:
  //
  // Static variable will only be decleared once and
  // will retain its last assigned value until the entire
  // program exits
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  //
  // The tick rate (configTICK_RATE_HZ) is defined in FreeRTOSConfig.h,
  // the default rate is 1000 (1KHz), so one tick is equivalent to 1 ms
  //
  // It is similar to the timer we used before, but you'll
  // need to calculate the time elapsed by taking the difference
  // between curr_tick and prev_tick.
  curr_onoff_tick_time = xTaskGetTickCount();

  // STEP 3
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual StartStop button has been
  // pressed for 2 seconds and needs to set the global flags accordingly
  //
  // Task function should never return so is typically
  // implemented as an infinite loop
  //
  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
      
  while (1) {
    curr_onoff_tick_time = xTaskGetTickCount();
    // Check whether the virtual button is pressed.
    /*
    if(touch_readX() > some value){//check if S button is pressed
      //FOR more than 2 sec


*/
    unsigned long x = Touch_ReadX(); 
     
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if ((x>810 && x<1200)) { // if S button is pressed
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 300) {
        // Set the global flag
        onoff_status = 1;
        // Clear the timer
        prev_onoff_tick_time = curr_onoff_tick_time;
      }
      else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      onoff_status = 0;
      // Clear the timer
      prev_onoff_tick_time = curr_onoff_tick_time;
    }

    vTaskDelay(1);
  }
}

void Pedestrian(void *p) {
  static int curr_ped_tick_time = 0;
  static int prev_ped_tick_time = 0;

  // STEP 4
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual pedestrian button has been pressed
  // for 2 seconds and update the global flag accordingly.
  //
  // (Refer to instructions in the StartStop function to implement
  // this function.)
  
  while (1) {
    unsigned long x = Touch_ReadX(); 

    curr_ped_tick_time = xTaskGetTickCount();
    //if the button has been pressed
    if (x>1300 && x<1600) { // Check P button
      if (curr_ped_tick_time - prev_ped_tick_time >= 300) {
        // Set the global flag
        pedestrian_status = 1;
        // Clear the timer
        prev_ped_tick_time = curr_ped_tick_time;
      }
      else {
        // Clear the global flag
        pedestrian_status = 0;
      }
    } else {
      // Clear the global flag
      pedestrian_status = 0;
      // Clear the timer
      prev_ped_tick_time = curr_ped_tick_time;
      
    }

    vTaskDelay(1);
  }
}
void Control(void *p) {
  static int curr_light_tick_time = 0;
  static int prev_light_tick_time = 0;

  // STEP 5
  //
  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_light_tick_time = xTaskGetTickCount();

    // If the one of the virtual lights been lighting up for 5 or more
    // seconds, or if any of the virtual button flags has been set, switch
    // to the corresponding next state and reset the light tick.
    //if neither ped or sys button is pressed
      // Reset the light tick
    if((curr_light_tick_time - prev_light_tick_time >= 1500) || pedestrian_status || onoff_status) {
        //clear timer
        prev_light_tick_time = curr_light_tick_time;
      // Switch to next state
        FSM();
    }

    vTaskDelay(1);
  }
}
//RED, YEL, and GRN are the unsigned ints to be used as parameters of LED_on
//each variable corresponds to pins on port L
unsigned int RED = 0x04;
unsigned int YEL = 0x08;
unsigned int GRN = 0x10;
//turns on LED if given the right pin (color)
void LED_on(unsigned int COL)
{
  if(COL == RED){ //RED LIGHT
    LCD_DrawFilledCircle(256,72,20,Color4[12]);
  } else if(COL == YEL){//YELLOW LIGHT
    LCD_DrawFilledCircle(256,120,20,Color4[14]);
  } else if(COL == GRN){//GREEN LIGHT
    LCD_DrawFilledCircle(256,168,20,Color4[10]);
  } 

}
//turns off all LEDs
void LED_off(void)
{
  LCD_DrawFilledCircle(256,72,20, Color4[0]);
  LCD_DrawFilledCircle(256,120,20,Color4[0]);
  LCD_DrawFilledCircle(256,168,20,Color4[0]);
}
enum TL_States {TL_start, TL_green, TL_yellow, TL_red} TL_State;
int on;
int p;
int off;
void FSM(void) { 
  //if S button is being pressed and it hasn't turned on yet
    if(onoff_status && !on){
      on = 1;//turn on system
      //When we first start the program this text helps us know when to let go of
      //the S button
      LCD_SetCursor(0,0);
      LCD_PrintString("Ready!");
    } 
    if(on == onoff_status){ //if button is being pressed while it's on
      off = 1; //turn off the system
      on = 0;
      onoff_status = 0;
    } else {
      off = 0;
      on = 1;
    }
    
    if(pedestrian_status){//if P button is pressed
      p = 1; //activate pedestrian function
    }
  // STEP 6
  //
  // Add your FSM implementation here.
  // This function will be called by the control task function.
  switch(TL_State){
    case TL_start: 
      if(on){ //if system is on
        LED_off();
        LED_on(RED);//turn on red LED and go to stop state
        TL_State = TL_red;  
        break;
      } else {
        on = 0;
        LED_off();
      }
      break;
      
    case TL_green:
      if(off){//if system off then go to start state
        LED_off();
        TL_State = TL_start;
        break;
      }
      if(p){ //if pedestrian function on then go to warn state
        LED_off();
        LED_on(YEL);
        TL_State = TL_yellow;
        break;
      } 
      p = 0;//otherwise turn off pedestrian function and toggle to stop state
      LED_off();
      LED_on(RED);
      TL_State = TL_red;
      
     break;  
      
    case TL_yellow:
      if(off){//if system is off then go to start state
        LED_off();
        TL_State = TL_start;
        break;
      }
      //otherwise toggle to stop state
      LED_off();
      LED_on(RED);
      TL_State = TL_red;
      
      break;  
      
    case TL_red:
      if(off){//if system is off then go to start state
        LED_off();
        TL_State = TL_start;
        break;
      } else if (pedestrian_status){//if P button is currently being pressed stay red
        TL_State = TL_red;
      }
      LED_off();//otherwise go to start state
      LED_on(GRN);
      TL_State = TL_green;        
      break;
     
   }
    
}
