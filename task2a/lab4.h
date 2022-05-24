#ifndef __HEADER1_H__
#define __HEADER1_H__


//RCGC Register Definitions
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608))
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define RCGCADC      (*((volatile uint32_t *)0x400FE638)) //Enable clock to ADC
#define RCGCUART     (*((volatile uint32_t *)0x400FE618)) //Enable clock to UART

//UART Module 0 Register Definitons
#define UARTIBRD0    (*((volatile uint32_t *)0x4000C024)) 
#define UARTFBRD0    (*((volatile uint32_t *)0x4000C028)) 
#define UARTLCRH0    (*((volatile uint32_t *)0x4000C02C)) 
#define UARTCTL0     (*((volatile uint32_t *)0x4000C030)) 
#define UARTCC0      (*((volatile uint32_t *)0x4000CFC8)) 
#define UARTDMACTL0  (*((volatile uint32_t *)0x4000C028)) 
#define UARTDR0      (*((volatile uint32_t *)0x4000C000)) 
#define UARTFR0      (*((volatile uint32_t *)0x4000C018)) 
#define UARTICR0     (*((volatile uint32_t *)0x4000C044)) 


//UART Module 2 Register Definitons
#define UARTIBRD2    (*((volatile uint32_t *)0x4000E024)) 
#define UARTFBRD2    (*((volatile uint32_t *)0x4000E028)) 
#define UARTLCRH2    (*((volatile uint32_t *)0x4000E02C)) 
#define UARTCTL2     (*((volatile uint32_t *)0x4000E030)) 
#define UARTCC2      (*((volatile uint32_t *)0x4000EFC8)) 
#define UARTDMACTL2  (*((volatile uint32_t *)0x4000E028)) 
#define UARTDR2      (*((volatile uint32_t *)0x4000E000)) 
#define UARTFR2      (*((volatile uint32_t *)0x4000E018)) 
#define UARTICR2     (*((volatile uint32_t *)0x4000E044)) 
#define UARTIM2      (*((volatile uint32_t *)0x4000E038)) 



//ADC Register Definitions
#define ADCCC        (*((volatile uint32_t *)0x40038FC8))//ADC Clock Config
#define ADCACTSS     (*((volatile uint32_t *)0x40038000))//Active Sample Sequencer
#define ADCEMUX      (*((volatile uint32_t *)0x40038014))//Event Mux Select
#define ADCSSMUX3    (*((volatile uint32_t *)0x400380A0))//Sample Input Mux sel.
#define ADCSSEMUX3   (*((volatile uint32_t *)0x400380B8))
#define ADCSSCTL3    (*((volatile uint32_t *)0x400380A4))//SS3
#define ADCTSSEL     (*((volatile uint32_t *)0x4003801C))
#define ALTCLKCFG    (*((volatile uint32_t *)0x400FE138)) //Alt. Clock Config
#define ADCIM        (*((volatile uint32_t *)0x40038008)) //ADC Interrupt Mask
#define GPTMADCEV    (*((volatile uint32_t *)0x40030070)) 
#define ADCSSFIFO3   (*((volatile uint32_t *)0x400380A8)) 
#define ADCISC       (*((volatile uint32_t *)0x4003800C)) 



//Timer Register Definitions
#define GPTMCTL0     (*((volatile uint32_t *)0x4003000C))
#define GPTMCTL1     (*((volatile uint32_t *)0x4003100C))

#define GPTMCTFG0     (*((volatile uint32_t *)0x40030000))
#define GPTMCTFG1     (*((volatile uint32_t *)0x40031000))

#define GPTMTAMR0     (*((volatile uint32_t *)0x40030004))
#define GPTMTAMR1     (*((volatile uint32_t *)0x40031004))

#define GPTMTAILR0   (*((volatile uint32_t *)0x40030028))
#define GPTMTAILR1   (*((volatile uint32_t *)0x40031028))

#define GPTMIMR0     (*((volatile uint32_t *)0x40030018))
#define GPTMIMR1     (*((volatile uint32_t *)0x40031018))

#define GPTMRIS0     (*((volatile uint32_t *)0x4003001C))
#define GPTMRIS1     (*((volatile uint32_t *)0x4003101C))

#define GPTMICR0     (*((volatile uint32_t *)0x40030024))
#define GPTMICR1     (*((volatile uint32_t *)0x40031024))

#define EN0          (*((volatile uint32_t *)0xE000E100))

//Register definitions for port A
#define GPIOAMSEL_A  (*((volatile uint32_t *)0x40058528)) 
#define GPIOPCTL_A   (*((volatile uint32_t *)0x4005852C)) 
#define GPIODEN_A    (*((volatile uint32_t *)0x4005851C)) 
#define GPIOAFSEL_A  (*((volatile uint32_t *)0x40058420)) 
#define GPIODATA_A   (*((volatile uint32_t *)0x400583FC))
#define GPIOPCTL_A   (*((volatile uint32_t *)0x4005852C))


//Register definitions for port F
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC))

//Register definitions for port J
#define GPIODIR_J    (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510))

//Register definitions for port C
#define GPIOAMSEL_C  (*((volatile uint32_t *)0x4005A528))
#define GPIODIR_C    (*((volatile uint32_t *)0x4005A400))
#define GPIODEN_C    (*((volatile uint32_t *)0x4005A51C))
#define GPIOAFSEL_C  (*((volatile uint32_t *)0x4005A420))
#define GPIODATA_C   (*((volatile uint32_t *)0x4005A3FC))

//Register definitions for port N
#define GPIOAMSEL_N  (*((volatile uint32_t *)0x40064528)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIOAFSEL_N  (*((volatile uint32_t *)0x40064420)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC))

//Register definitions for port L
#define GPIOAMSEL_L  (*((volatile uint32_t *)0x40062528)) 
#define GPIODIR_L    (*((volatile uint32_t *)0x40062400)) 
#define GPIODEN_L    (*((volatile uint32_t *)0x4006251C)) 
#define GPIOAFSEL_L  (*((volatile uint32_t *)0x40062420)) 
#define GPIODATA_L   (*((volatile uint32_t *)0x400623FC))

//Register definitions for port E
#define GPIOAMSEL_E  (*((volatile uint32_t *)0x4005C528)) 
#define GPIODIR_E    (*((volatile uint32_t *)0x4005C400)) 
#define GPIODEN_E    (*((volatile uint32_t *)0x4005C51C)) 
#define GPIOAFSEL_E  (*((volatile uint32_t *)0x4005C420)) 
#define GPIODATA_E   (*((volatile uint32_t *)0x4005C3FC))
#endif //__HEADER1_H__