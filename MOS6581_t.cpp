#include "MOS6581_t.h"


MOS6581_t::MOS6581_t(byte _cs_pin, byte r_w_pin)
    :_CS(_cs_pin), R_W(r_w_pin)
{}

void MOS6581_t::select_register(registers_t address) const {}

void MOS6581_t::write_data(byte data) const {}

byte MOS6581_t::read_data() const {}


byte MOS6581_t::get_last_address() const
{
    return last_address;
}

byte MOS6581_t::get_last_write() const
{
    return last_write;
}

byte MOS6581_t::get_last_read() const
{
    return last_read;
}

byte MOS6581_t::peek(registers_t address)
{
    digitalWrite(R_W, HIGH);
    select_register(address);
    digitalWrite(_CS, LOW);
    delayMicroseconds(1);

    return read_data();
}
