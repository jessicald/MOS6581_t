#include "MOS6581_t.h"


MOS6581_t::MOS6581_t(byte _cs_pin, byte r_w_pin)
    :_CS(_cs_pin), R_W(r_w_pin)
{}

void MOS6581_t::select_register(registers_t) {}

void MOS6581_t::write_data_pins(byte) {}

byte MOS6581_t::read_data_pins() {}


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

/* http://www.bot-thoughts.com/2011/06/generate-clock-signal-with-avr-atmega.html */
void MOS6581_t::start_clock(byte o2_pin)
{
    O2 = o2_pin;
    // Set Clock to Output
    pinMode(O2, OUTPUT);

    TCNT1=0;
    // Toggle OC1A on Compare Match
    TCCR1A = 0x00;
    bitSet(TCCR1A, COM1A0);
    // Clear Timer on Compare Match
    TCCR1B = 0x00;
    bitSet(TCCR1B, WGM12);
    // Set frequency (1 MHz)
    OCR1A = 8;
    // No prescaling
    bitSet(TCCR1B, CS10);
}

