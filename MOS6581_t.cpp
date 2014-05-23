#include "MOS6581_t.h"


MOS6581_t::MOS6581_t(byte _cs_pin, byte r_w_pin)
    :_CS(_cs_pin), R_W(r_w_pin)
{}

void MOS6581_t::select_register(registers_t) const {}

void MOS6581_t::write_data_pins(byte) const {}

byte MOS6581_t::read_data_pins() const {}


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

byte MOS6581_t::PEEK(registers_t address)
{
    digitalWrite(R_W, HIGH);
    select_register(address);
    digitalWrite(_CS, LOW);
    delayMicroseconds(1);
    
    byte value = read_data_pins();
    digitalWrite(_CS, HIGH);

    return value;
}

void MOS6581_t::POKE(registers_t address, byte value)
{
    digitalWrite(R_W, LOW);
    select_register(address);
    digitalWrite(_CS, LOW);
    delayMicroseconds(1);
    
    write_data_pins(value);
    delayMicroseconds(1);
    digitalWrite(_CS, HIGH);

    return;
}
