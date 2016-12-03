#include"gamepad.h"

int main (void)
{
    uint8_t value = 0;
    uint16_t value1 = 0;
    DDRB = 0xff;
    DDRC = 0xff;
    psxinit ();

    while (1)
    {
        readgamepad ();
        value1 = psxbutton ();          // these buttons are used for the movement of parent bot

        if ((value1 & psxTri) > 0)      // up button
        {
            sbi (PORTB, ledPin1);       //led pin on
        }
        else
        {
            cbi (PORTB, ledPin1);       //led pin off
        }

        if ((value1 & psxSqu) > 0)      // left button
        {
            sbi (PORTB, ledPin2);
        }
        else
        {
            cbi (PORTB, ledPin2);
        }

        if ((value1 & psxX) > 0)        // down button
        {
            sbi (PORTB, ledPin3);       
        }
        else
        {
            cbi(PORTB, ledPin3);
        }

        if ((value1 & psxO) > 0)        // right button
        {
            sbi (PORTB, ledPin4);
        }
        else
        {
            cbi (PORTB, ledPin4);
        }

        // analog stick is used for the movement of parent bot's arms
        value = psxstick (5);           // analog stick value for right joystick x-axis
        PORTC = value;
        value = psxstick (6);           // analog stick value for right joystick y-axis
        PORTC = value;
        value = psxstick (7);           // analog stick value for left joystick x-axis
        PORTC = value;
        value = psxstick (8);           // analog stick value for left joystick x-axis
        PORTC = value;
    }
    return 0;
}
