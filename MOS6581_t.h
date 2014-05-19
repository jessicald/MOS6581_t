#ifndef MOS6581_T_H
#define MOS6581_T_H


#include <Arduino.h>


/* Base class for the SID, holds all information common to both parallel and serial implementations. */
class MOS6581_t
{
protected:

    /* The chip select pin, which must be low in order to interface with the SID's registers. */
    const byte _CS;
    /* Operation select pin.  Read is HIGH, Write is LOW. */
    const byte R_W;

public:

    static const byte ADDR_PIN_COUNT = 5;
    static const byte DATA_PIN_COUNT = 8;

    MOS6581_t(byte _cs_pin, byte r_w_pin);

    /* Selects the register address to read to or write from.
     * Implemeneted by subclasses.
     */
    virtual void select_address(byte address) const {}
};


#endif
