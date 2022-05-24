// _________ HEADER FILE (task2a_functions.h) _________
/*
  Abdulrahman Adam
  2076566
  December 4, 2021
  This is the header file that is used in lab 4 task 2a
  this holds all the prototype functions and state machine
*/


#ifndef __HEADER2_H__
#define __HEADER2_H__


/*This function initializes and configures the ports that are to be used 
for the external LEDS on the breadboard*/
int second = 16000000;
void GPIO_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1524;    // Enable PortF, PortN, PortC, PortL, and PortJ RCGCGPIO
  delay++;
  delay++;
  
  GPIOAMSEL_L &= ~0x1C; //disable analog function for PL0, PL1, PL2, PL3, PL4
  GPIODIR_L |= 0x1C;    //set PL2, PL3, and PL4 to outputs
  GPIOAFSEL_L &= ~0x1C; //set PL2, PL3, and PL4 regular port functions
  GPIODEN_L |= 0x1F;    //enable digital port for PL2, PL3, and PL4
  
  GPIODIR_F = 0x11;      // Set PF0 and PF4 to output
  GPIODEN_F = 0x11;      // Set PF0 and PF4 to digital port
  
  GPIODIR_N = 0x03;      // Set PN0 and PN1 to output
  GPIODEN_N = 0x03;      // Set PN0 and PN1 to digital port
}
void Timer_init0(){
  RCGCTIMER |= 0x01; //Enable appropriate TIMERn bit
  GPTMCTL0 &= ~0x1; //Disable timer
  GPTMCTFG0 |= 0x00000000; //Load 0 into GPTMCFG for 32-bit timer config
  GPTMTAMR0 |= 0x0002; // configure register to be in periodic timer mode
  GPTMTAMR0 &= ~0x010; //configure TACDIR bit of register to countdown
  GPTMTAILR0 = 50000000; //load 50,000,000 for 60MHz 
  GPTMCTL0 |= 0x0001; //Enable timer
  EN0 |= 0x80000; //Enable EN0 with 19th bit set for Timer0A
  GPTMIMR0 |= 0x1;
}

//RED, YEL, and GRN are the unsigned ints to be used as parameters of LED_on
//each variable corresponds to pins on port L
unsigned int RED = 0x04;
unsigned int YEL = 0x08;
unsigned int GRN = 0x10;

//turns off all LEDs
void LED_off(void)
{
  LCD_DrawFilledCircle(256,72,20, Color4[0]);
  LCD_DrawFilledCircle(256,120,20,Color4[0]);
  LCD_DrawFilledCircle(256,168,20,Color4[0]);
}



//checks to see if the switch corresponding to the Pedestrian button is set
unsigned long switch_P() 
{ 
  unsigned long x = Touch_ReadX(); 
  unsigned long y = Touch_ReadY();
  return (x>1300 && x<1600); // 0x2 (pressed) or 0 (not pressed) 
} 

//checks to see if the switch corresponding to the System On/Off button is set
unsigned long switch_S() 
{ 
  unsigned long x = Touch_ReadX(); 
  unsigned long y = Touch_ReadY();
  return (x>810 && x<1200); // 0x1 (pressed) or 0 (not pressed) 
} 



//SM name: Traffic Light (or TL)
enum TL_States {TL_start, TL_green, TL_yellow, TL_red, TL_OFF} TL_State;
int t; //t works to check if we are toggling between red and green
int on; // on is true when system is on, we start with the system off
int off;
//these variables are used as counters to check how long switch is pressed
unsigned int pedestrian;
unsigned int system;
unsigned int state;

unsigned int ped_change; //true every time the "pedestrian" counter is pushed for 2 sec
unsigned int sys_change; //true every time the "system" coounter is pushed for 2 sec
unsigned int state_change;//true if neither sys_change nor ped_change is true 


void Timer0A_Handler(void){ // every 1 second
  //everytime sysOn/Off button is pressed, we will increment this variable
  //until it reaches 2 seconds then restart
  if(switch_S()){
    sys_change = 1; 
  }
 
  if(sys_change && !on){
    on = 1;
    LCD_SetCursor(0,0);
    LCD_PrintString("Ready!");
    sys_change = 0;
  } else if(!on){
    LCD_SetCursor(0,0);
    LCD_PrintString("");
  }
  if(on == sys_change){
    off = 1;
    on = 0;
    sys_change = 0;
  } else {
    off = 0;
    on = 1;
  }
  if(switch_P()){
    ped_change = 1;
  } 
  if(!ped_change && !sys_change && on){
    state++;
  } 
  if(state == 2){
    state = 0;
    state_change = 1;
  }
    
   switch(TL_State){
    case TL_start: 
      //we start with our system going into the off state if on = 0
      if(on){
        state_change = 0;
        LED_off();
        LED_on(RED);
        TL_State = TL_red;
      } else if(off){ //if system is on we go to the red state
        on = 0;
        sys_change = 0;
        TL_State = TL_OFF;;
      }
      break;
      
    case TL_green:
      //if pedestrian input, we go to yellow state
      if(ped_change){
        LED_off();
        LED_on(YEL);
        TL_State = TL_yellow;
        break;
      } 
      //if switch S is pushed while on, we go to the off state
      if(off){
        on = 0;
        sys_change = 0;
        state_change = 0;
        TL_State = TL_OFF;
        break;
      } 
      //if state_change is true, we toggle back to the red state
      if(state_change){
        state_change = 0;
        LED_off();
        LED_on(RED);
        TL_State = TL_red;
        break;
      }
      break;  
      
    case TL_yellow:
      //LED_off();
//      LED_on(YEL);
      //if switch s is pushed while on, we go to the off state
      if(off){
        on = 0;
        sys_change = 0;
        TL_State = TL_OFF;
      }
      ped_change = 0;
      if(state_change){//if we are changing states (every 5 seconds)
        state_change = 0;//clear state_change
        LED_off();
        LED_on(RED);
        TL_State = TL_red;//go to the red state
      }
      break;  
      
      
    case TL_red:
      //if switch s is pushed while on, we go to the off state
      if(off){
        on = 0;
        sys_change = 0;
        TL_State = TL_OFF;
      } 

      //if we are toggling then go back to green state
      if(state_change){
        state_change = 0;
        LED_off();
        LED_on(GRN);        
        TL_State = TL_green;
        break;
      }

      break;
        
    case TL_OFF:
      LED_off();
      //if off and system switch is pushed, then we go back to the start state
      if(on){
        on = 1;
        sys_change = 0;//clear sys_change counter
        state_change = 0;//clear sys_change coutner
        TL_State = TL_start;
      }

      break;
     
   }
  GPTMICR0 =  1;  
   
}
    

#endif //__HEADER2_H__