#include"gamepad.h"

static uint8_t _data[21];                     // response from ps2 is stored in _data array

//sending and receiving the data serially one byte at a time
//bit-banging command and clock lines to transmit command to
//the gamepad and receive data bytes on data line.
uint8_t shift (uint8_t command)
{
    uint8_t i = 0;
    uint8_t recvdByte = 0;
    for (i = 0; i < 8; i++)
    {
        cbi (GPORT, clock);                   // drop the clock
        if (command & bv (i))
        {
            sbi (GPORT, cmnd);                // set command pin
        }
        else
        {
            cbi (GPORT, cmnd);                // clear command pin
        }
        _delay_us (10);                       // wait for half the clock cycle
        sbi (GPORT, clock);                   // raise the clock high

        if (PIND & bv (data))                 // reading data pin
        {
            sbi (recvdByte, i);
        }
        _delay_us (10);                       // wait for another half of the clock cycle
    }
    sbi (GPORT, clock);                       // clock should be high at this time
    return recvdByte;
}

//send a command using the shift method
// before submitting each command packet,we must set attention pin low and once 
// we are done,return it high.
void psxCommand (uint8_t send_data[], uint8_t size)
{
    cbi (GPORT, att);                         //set attention pin low
    sbi (GPORT, cmnd);
    sbi (GPORT, clock);
    
    uint8_t i = 0;
    for (i = 0; i < size; i++)
    {
        _data[i] = shift (send_data[i]);
    }
    sbi (GPORT, att);                         //set attention pin high
}

// reads the gamepad.We need to call this whenever we want updated status
void readGamepad ()
{
    _data[0] = 0x01;                          // command for starting of packets
    _data[1] = 0x42;                          // command for polling or configuring gamepad
    
    uint8_t i = 0;
    for (i = 2; i < 21; i++)
    {
        _data[i] = 0x00;                      // this command is used to get the values of the buttons and joysticks 
    }
    psxCommand (_data, 21);
}

// initializing the pins and setting the controller up to the correct mode
void psxInit ()
{
    sbi (GDDR, clock);                        // making pin output
    sbi (GDDR, att);
    sbi (GDDR, cmnd);
    cbi (GDDR, data);                         // making pin input

    sbi (GPORT, data);                        // activate pull-up for data pin
    sbi (GPORT, clock);
    sbi (GPORT, cmnd);

    readGamepad ();                           // initializing by polling once
    
    uint8_t config[] = {0x01, 0x43, 0x00, 0x01, 0x00};// enter config mode
    psxCommand (config, 5);
    
    uint8_t lock_analog[] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};// lock to analog mode on joystick
    psxCommand (lock_analog, 9);
    
    uint8_t exit[] = {0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};// exit config mode
    psxCommand (exit, 9);
}

// returns the value of the given analog stick (0-255)
uint8_t psxStick (uint8_t stick)
{
    return (_data[stick]);
}

// returns the current state of all 16 buttons
uint16_t psxButton ()
{
    uint16_t buttons = *(uint16_t *)(_data + 3);
    return ~buttons;
}
