#ifndef MOS6581_P_H
#define MOS6581_P_H

#include <Arduino.h>
#include "MOS6581_t.h"


class MOS6581_p: public MOS6581_t
{
    /* Parallel implementation of SID control; microcontroller pins connect in parallel to SID address
     * and data pins, possibly in combination with other chips on a bus.
     */

private:

    /* The parallel address-select pins that control which of the SID's registers to write to or read from.
     * Pin order:  A0, A1, A2, A3, A4
     */
    byte ADDR[ADDR_PIN_COUNT];

    /* The parallel data pins used to write to or read from the selected register.
     * Pin order:  D0, D1, D2, D3, D4, D5, D6, D7
     */
    byte DATA[DATA_PIN_COUNT];



public:

    MOS6581_p(const byte address_pins[ADDR_PIN_COUNT], const byte data_pins[DATA_PIN_COUNT],
              byte _cs_pin, byte r_w_pin);

    /* Writes the address pins to the address provided.
     * The MSB is A4, the LSB is A0.
     */
    void select_address(registers_t address);

    /* Writes the data pins with the data provided.
     * The MSB is D7, the LSB is D0.
     */
    void output_data(byte data);
};


#endif
