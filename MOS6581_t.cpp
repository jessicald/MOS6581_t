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

/* http://www.cemetech.net/forum/viewtopic.php?t=7763 */
// void MOS6581_t::start_clock()
// {
//     DDRB = _BV(DDB1);                  //set OC1A/PB1 as output (Arduino pin D9, DIP pin 15)
//     TCCR1A = _BV(COM1A0);              //toggle OC1A on compare match
//     OCR1A = 7;                         //top value for counter
//     TCCR1B = _BV(WGM12) | _BV(CS10);   //CTC mode, prescaler clock/1
// }

// (3, OC2B), (5, OC0B), (6, OC0A), (9, OC1A), (10, OC1B), (11, OC2A)
/* http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=50106 */
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
int MOS6581_t::start_clock(byte o2_pin)
{
    volatile void *timer_control_a_r, *timer_control_b_r, *compare_match_value_r;
    byte compare_match_output;

    switch (o2_pin)
    {
    case 9:
        timer_control_a_r = &TCCR1A;
        timer_control_b_r = &TCCR1B;
        compare_match_output = COM1A0;
        compare_match_value_r = &OCR1A;
        break;
    case 10:
        timer_control_a_r = &TCCR1A;
        timer_control_b_r = &TCCR1B;
        compare_match_output = COM1B0;
        compare_match_value_r = &OCR1B;
        break;
    case 11:
        timer_control_a_r = &TCCR2A;
        timer_control_b_r = &TCCR2B;
        compare_match_output = COM2A0;
        compare_match_value_r = &OCR2A;
        break;
    case 3:
        timer_control_a_r = &TCCR2A;
        timer_control_b_r = &TCCR2B;
        compare_match_output = COM2B0;
        compare_match_value_r = &OCR2B;
        break;
    default:
        return o2_pin;
    }


    O2 = o2_pin;
    pinMode(O2, OUTPUT);
    
    // // /* Initialize timer */
    // // TCNT1 = 0;
    // /* Toggle OC1A and Clear Timer on Compare Match */
    // TCCR1A = 0x00 | _BV(COM1A0) | _BV(WGM12);    /* No prescaling */
    // TCCR1B = 0x00 | _BV(CS10);
    // /* Set frequency (1 MHz) */
    // OCR1A = 8;

    /* Toggle OC1A and Clear Timer on Compare Match */
    
    *static_cast<volatile byte*>(timer_control_a_r) = 0 | _BV(compare_match_output) | _BV(WGM12);    /* No prescaling */
    *static_cast<volatile byte*>(timer_control_b_r) = 0 | _BV(CS10);
    /* Set frequency (1 MHz) */
    *static_cast<volatile byte*>(compare_match_value_r) = 8;
    
    // (3, OC2B), (5, OC0B), (6, OC0A), (9, OC1A), (10, OC1B), (11, OC2A)



    // /* Clear Timer on Compare Match */
    // // TCCR1B = 0x00;
    // // bitSet(TCCR1B, WGM12);
    // TCCR1B = 0x00 | _BV(WGM12);

    return 0;
}

