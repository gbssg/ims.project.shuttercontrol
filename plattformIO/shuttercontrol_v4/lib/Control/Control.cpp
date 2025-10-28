#include "Control.h"

const sAddressDescriptor address[] = {
    {.addrB1 = 0x6F, .addrB2 = 0x71},
    {.addrB1 = 0x72, .addrB2 = 0x73},
};



void setupControl(tControl * me, tMotor * motor, int addressNr, QwiicButton buttonUp, QwiicButton buttonDown)
{
    me->desc = &address[addressNr];
    me->button->up = &buttonUp;
    me->button->down = &buttonDown;
    me->button->up->begin(me->desc->addrB1);
    me->button->down->begin(me->desc->addrB2);
}