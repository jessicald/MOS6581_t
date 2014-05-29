#ifndef MOS6581_T_H
#define MOS6581_T_H


#include <Arduino.h>


class MOS6581_t
{
    /* Base class for the SID, holds all information common to both parallel and serial implementations. */
protected:
    byte last_address, last_write, last_read;
    byte O2;

public:

    /* Parallel pin counts. */
    static const byte ADDR_PIN_COUNT = 5;
    static const byte DATA_PIN_COUNT = 8;

    enum registers_t {v1_freq_lo,
                      v1_freq_hi,
                      v1_pw_lo,
                      v1_pw_hi,
                      v1_control,
                      v1_ad,
                      v1_sr,
                           
                      v2_freq_lo,
                      v2_freq_hi,
                      v2_pw_lo,
                      v2_pw_hi,
                      v2_control,
                      v2_ad,
                      v2_sr,
                           
                      v3_freq_lo,
                      v3_freq_hi,
                      v3_pw_lo,
                      v3_pw_hi,
                      v3_control,
                      v3_ad,
                      v3_sr,

                      filter_fc_lo,
                      filter_fc_hi,
                      filter_res_filt,
                      filter_mode_vol,

                      misc_potx,
                      misc_poty,
                      misc_osc3_random,
                      misc_env3,
    };


    /* The chip select pin, which must be low in order to interface with the SID's registers. */
    const byte _CS;
    /* Operation select pin.  Read is HIGH, Write is LOW. */
    const byte R_W;


    MOS6581_t(byte _cs_pin, byte r_w_pin);


    /* Accessor method for the stored address. */
    byte get_last_address() const;

    /* Accessor method for the stored last write. */
    byte get_last_write() const;

    /* Accessor method for the stored last read. */
    byte get_last_read() const;


    /* Writes the address pins with the bits of `address`.
     * Implemented by subclasses.
     */
    virtual void select_register(registers_t address);

    /* Writes the data pins with the bits of `value`.
     * Implemented by subclasses.
     */
    virtual void write_data_pins(byte value);

    /* Returns the values read on the data pins as an unsigned eight bit field.
     * Implemented by subclasses.
     */
    virtual byte read_data_pins();


    /* Implementation of the PEEK command from BASIC.
     * Returns the contents of the register at `address`.
     */
    byte PEEK(registers_t address);
    
    /* Implementation of the POKE command from BASIC.
     * Writes the register at `address` with the data `value`.
     */
    void POKE(registers_t address, byte value);

    /* Generates a 1 MHz clock signal for the SID using AVR's hardware timers.
     * Returns 0 if successful or `o2_pin` if not.
     * Valid values of `o2_pin`:  3, 9, 10, 11
     *
     * (These pins are only valid for the ATmega168/328. On these versions of Arduino,
     * pins 9 and 10 use Timer1, 3 and 11 use Timer2.  Pin 11 is also used by the ICSP header.
     * Keep these in mind if using other libraries or an external programmer.)
     */
    byte start_clock(byte o2_pin);
};


#endif
