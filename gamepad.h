#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

#ifndef GAMEPAD_H
#define GAMEPAD_H

#define clock 3 
#define cmnd 1 
#define data 0 
#define att 2  
#define sbi(x,y) (x |= (1 << y)) // setting pin high
#define cbi(x,y) (x &= (~(1 << y))) // setting pin low
#define bv(y) (1 << y) // shifting

// buttons constants
#define psxLeft	 0x0001 
#define psxDown	 0x0002
#define psxRight 0x0004
#define psxUp	 0x0008
#define psxStrt	 0x0010
#define psxSlct	 0x0080
#define psxSqu	 0x0100
#define psxX	 0x0200
#define psxO	 0x0400
#define psxTri	 0x0800
#define psxR1	 0x1000
#define psxL1	 0x2000
#define psxR2	 0x4000
#define psxL2	 0x8000

// led pins for showing response from ps2
#define ledPin1  0     
#define ledPin2  1
#define ledPin3  2
#define ledPin4  3

extern uint8_t shift (uint8_t command);
extern uint8_t psxstick (uint8_t);
extern uint16_t psxbutton (void);
extern void psxinit (void);
extern void psxcommand (uint8_t send_data[], uint8_t size);
extern void readgamepad (void);
#endif
