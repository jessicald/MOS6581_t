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


void MOS6581_p::select_register(registers_t address)
{
    for (byte i = 0; i < ADDR_PIN_COUNT; i++)
        digitalWrite(ADDR[i], address & (1 << i));

    last_address = address;
}


void MOS6581_p::write_data_pins(byte value)
{
    for (byte i = 0; i < DATA_PIN_COUNT; i++)
        digitalWrite(DATA[i], value & (1 << i));

    last_write = value;
}

byte MOS6581_p::read_data_pins()
{
    byte input = 0;
    for (byte i = 0; i < DATA_PIN_COUNT; i++)
        input |= digitalRead(DATA[i]) << i;

    last_read = input;
    return input;
}
