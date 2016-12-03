#include"gamepad.h"

static uint8_t _data[21];// response from ps2 is stored in _data array

uint8_t shift (uint8_t command)//sending and receiving the data serially one byte at a time
{
    uint8_t i;
    uint8_t datas = 0;
    for (i = 0; i < 8; i++)
    {
        cbi (PORTD, clock);// drop the clock
        if (command & bv (i))
        {
            sbi (PORTD, cmnd);// set command pin
        }
        else
        {
            cbi (PORTD, cmnd);
        }
        _delay_us (10);// wait for half the clock cycle
        sbi (PORTD, clock);// raise the clock high

        if (PIND & bv (data)) // reading data pin
        {
            sbi (datas, i);
        }
        _delay_us (10);// wait for another half of the clock cycle
    }
    sbi (PORTD, clock);// clock should be high at this time
    return datas;
}

void psxcommand (uint8_t send_data[], uint8_t size) //send a command using the shift method
{
    // before submitting each command packet,we must set attention pin low and once 
    // we are done,return it high.
    cbi (PORTD, att);
    sbi (PORTD, cmnd);
    sbi (PORTD, clock);
    
    uint8_t i = 0;
    for (i = 0; i < size; i++)
    {
        _data[i] = shift (send_data[i]);
    }
    sbi (PORTD, att);
}

void readgamepad () // reads the gamepad.We need to call this whenever we want updated status
{
    _data[0] = 0x01; // command for starting of packets
    _data[1] = 0x42; // command for polling or configuring gamepad
    
    uint8_t i = 0;
    for (i = 2; i < 21; i++)
    {
        _data[i] = 0x00; // this command is used to get the values of the buttons and joysticks 
    }
    psxcommand (_data, 21);
}

void psxinit () // initializing the pins and setting the controller up to the correct mode
{
    sbi (DDRD, clock);// making pin output
    sbi (DDRD, att);
    sbi (DDRD, cmnd);
    cbi (DDRD, data);// making pin input
    sbi (PORTD, data);
    sbi (PORTD, clock);
    sbi (PORTD, cmnd);
    readgamepad (); // initializing by polling once
    
    uint8_t config[] = {0x01, 0x43, 0x00, 0x01, 0x00};// enter config mode
    psxcommand (config, 5);
    
    uint8_t lock_analog[] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};// lock to analog mode on joystick
    psxcommand (lock_analog, 9);
    
    uint8_t exit[] = {0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};// exit config mode
    psxcommand (exit, 9);
}

uint8_t psxstick (uint8_t stick) // returns the value of the given analog stick (0-255)
{
    return (_data[stick]);
}

uint16_t psxbutton () // returns the current state of all 16 buttons
{
    uint16_t buttons = *(uint16_t *)(_data + 3);
    return ~buttons;
}
