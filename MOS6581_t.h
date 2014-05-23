#ifndef MOS6581_T_H
#define MOS6581_T_H


#include <Arduino.h>


class MOS6581_t
{
    /* Base class for the SID, holds all information common to both parallel and serial implementations. */
protected:
    byte last_address, last_write, last_read;

public:

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

    /* Accessor method for the stored write. */
    byte get_last_write() const;

    /* Accessor method for the stored read. */
    byte get_last_read() const;
    
    /* Selects the register address to read to or write from.
     * Implemented by subclasses.
     */
    virtual void select_register(registers_t address) const;

    /* Writes `data` to the current register.
     * Implemented by subclasses.
     */
    virtual void write_data(byte data) const;

    /* Reads the data from the current register and returns it.
     * Implemented by subclasses.
     */
    virtual byte read_data() const;

    byte peek(registers_t address);
};


#endif
