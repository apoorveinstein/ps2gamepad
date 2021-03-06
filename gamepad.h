#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

#ifndef GAMEPAD_H
#define GAMEPAD_H

#if !defined(GPORT) || !defined(GDDR)
#define GDDR  DDRD
#define GPORT PORTD
#endif

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

// data/control line pins
#define data     0
#define cmnd     1
#define att      2
#define clock    3

// macros for bit-wise operations
#define sbi(x,y) (x |= (1 << y))             // setting pin high
#define cbi(x,y) (x &= (~(1 << y)))          // setting pin low
#define bv(y) (1 << y)                       // shifting

// led pins for showing response from ps2
#define ledPin1  0     
#define ledPin2  1
#define ledPin3  2
#define ledPin4  3

extern uint8_t shift (uint8_t command);
extern uint8_t psxStick (uint8_t);
extern uint16_t psxButton (void);
extern void psxInit (void);
extern void psxCommand (uint8_t send_data[], uint8_t size);
extern void readGamepad (void);
#endif
