#include "MOS6581_p.h"


MOS6581_p::MOS6581_p(const byte* address_pins, const byte* data_pins,
                     byte _cs_pin, byte r_w_pin)
    :MOS6581_t(_cs_pin, r_w_pin)
{
    for (byte i = 0; i < ADDR_PIN_COUNT; i++)
        ADDR[i] = address_pins[i];

    for (byte i = 0; i < DATA_PIN_COUNT; i++)
        DATA[i] = data_pins[i];
}


void MOS6581_p::select_address(registers_t address)
{
    for (byte i = 0; i < ADDR_PIN_COUNT; i++)
        digitalWrite(ADDR[i], address & (1 << i));

    last_address = address;
}


void MOS6581_p::output_data(byte data)
{
    for (byte i = 0; i < DATA_PIN_COUNT; i++)
        digitalWrite(DATA[i], data & (1 << i));

    last_data = data;
}
