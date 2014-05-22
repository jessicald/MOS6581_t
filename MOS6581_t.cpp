#include "MOS6581_t.h"


MOS6581_t::MOS6581_t(byte _cs_pin, byte r_w_pin)
    :_CS(_cs_pin), R_W(r_w_pin)
{}

virtual void MOS6581_t::select_address(registers_t address) const {}

virtual void MOS6581_t::output_data(byte data) const {}

virtual byte MOS6581_t::input_data() const {}


byte MOS6581_t::get_last_address() const
{
    return last_address;
}

byte MOS6581_t::get_last_data() const
{
    return last_data;
}
    
byte MOS6581_t::peek(registers_t address)
{
    
}
