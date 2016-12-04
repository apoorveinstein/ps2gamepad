#include"gamepad.h"

#ifndef LEDPORT
#define LEDPORT PORTB
#endif

int main (void)
{
    uint8_t value = 0;
    uint16_t value1 = 0;
    DDRB = 0xff;
    DDRC = 0xff;
    psxInit ();

    while (1)
    {
        readGamepad ();
        value1 = psxButton ();          // these buttons are used for the movement of parent bot

        if ((value1 & psxTri) > 0)      // up button
        {
            sbi (LEDPORT, ledPin1);     //led pin on
        }
        else
        {
            cbi (LEDPORT, ledPin1);     //led pin off
        }

        if ((value1 & psxSqu) > 0)      // left button
        {
            sbi (LEDPORT, ledPin2);
        }
        else
        {
            cbi (LEDPORT, ledPin2);
        }

        if ((value1 & psxX) > 0)        // down button
        {
            sbi (LEDPORT, ledPin3);       
        }
        else
        {
            cbi(LEDPORT, ledPin3);
        }

        if ((value1 & psxO) > 0)        // right button
        {
            sbi (LEDPORT, ledPin4);
        }
        else
        {
            cbi (LEDPORT, ledPin4);
        }

        // analog stick is used for the movement of parent bot's arms
        value = psxStick (5);           // analog stick value for right joystick x-axis
        PORTC = value;
        value = psxStick (6);           // analog stick value for right joystick y-axis
        PORTC = value;
        value = psxStick (7);           // analog stick value for left joystick x-axis
        PORTC = value;
        value = psxStick (8);           // analog stick value for left joystick y-axis
        PORTC = value;
    }
    return 0;
}
