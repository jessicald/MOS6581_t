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

// /* http://www.cemetech.net/forum/viewtopic.php?t=7763 */
// void MOS6581_t::start_clock()
// {
//     DDRB = _BV(DDB1);                  //set OC1A/PB1 as output (Arduino pin D9, DIP pin 15)
//     TCCR1A = _BV(COM1A0);              //toggle OC1A on compare match
//     OCR1A = 7;                         //top value for counter
//     TCCR1B = _BV(WGM12) | _BV(CS10);   //CTC mode, prescaler clock/1
// }

// (3, OC2B), (5, OC0B), (6, OC0A), (9, OC1A), (10, OC1B), (11, OC2A)
// /* http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=50106 */
// int main (void) 
// { 
//    DDRD |= (1 << 5); // Set LED as output 
//    TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
//    TCCR1A |= (1 << COM1A0); // Enable timer 1 Compare Output channel A in toggle mode 
//    OCR1A   = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64 
//    TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64 
//    for (;;) 
//    { 
//    } 
// }


/* http://www.bot-thoughts.com/2011/06/generate-clock-signal-with-avr-atmega.html */
byte MOS6581_t::start_clock(byte o2_pin)
{
    /* Description of actions in `switch` statement:
     *
     * First line sets the Output Compare register (OCR) to 8, which with no prescaler
     * will match the timer twice every 16 clock cycles, one-sixteenth of the Arduino's
     * 16 MHz frequency.
     *
     * Second line sets the TCCR to disable prescaling/dividing of the clock.
     *
     * Third line sets the Timer/Counter Control register (TCCR) to toggle `o2_pin` *and*
     * zero the timer when it matches the value stored in OCR.  This will produce a rough
     * square wave with a frequency of 1 MHz.
     *
     * Final line zeros the Timer/Counter Register (TCNT, the timer itself).
     *
     *
     * TODO:  While the ATmega168/328 is the most prolific Arduino type, this function
     * should be generalized for versions of Arduino with different pin mappings.
     */

    switch (o2_pin)
    {
    case 9:  // Timer 1, AVR pin PB1/OC1A, Arduino pin 9
        OCR1A = 8;
        TCCR1B = 0 | _BV(CS10);
        TCCR1A = 0 | _BV(COM1A0) | _BV(WGM12);
        TCNT1 = 0;
        break;
    case 10:  // Timer 1, AVR pin PB2/OC1B, Arduino pin D11
        OCR1B = 8;
        TCCR1B = 0 | _BV(CS10);
        TCCR1A = 0 | _BV(COM1B0) | _BV(WGM12);
        TCNT1 = 0;
        break;
    case 11:  // Timer 2, AVR pin PB3/OC2A, Arduino pin 11
        OCR2A = 8;
        TCCR2B = 0 | _BV(CS10);
        TCCR2A = 0 | _BV(COM2A0) | _BV(WGM12);
        TCNT2 = 0;
        break;
    case 3:  // Timer 2, AVR pin PD3/OC2B, Arduino pin 3
        OCR2B = 8;
        TCCR2B = 0 | _BV(CS10);
        TCCR2A = 0 | _BV(COM2B0) | _BV(WGM12);
        TCNT2 = 0;
        break;
    default:
        return o2_pin;
    }

    O2 = o2_pin;
    /* The pin must be set to output mode before the timer circuitry can act on it. */
    pinMode(o2_pin, OUTPUT);

    return 0;
}

