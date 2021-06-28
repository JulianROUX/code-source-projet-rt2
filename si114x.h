#ifndef SI114X_H
#define SI114X_H


#include "mbed.h"
/*
 * Class to interface with Si114x sensors
 *
 * Currently only intended for Si1146. Should work also on the Si1145,
 * but the extra LED of the Si1147 is not supported. Everyone is welcome
 * to add this support and submit a pull request.
 *
 * Aditionally only synchronous mode is for now supported (no async I2C API is used
 * and the sensor is not placed in automatic measurement mode: Each request starts a new
 * measurement. Also for this and other issues: Everyone is welcome to submit
 * pull requests
 *
 * For now this is just returning raw values, no scaling is done by the library code
*/
class Si114x {
    public:
    /* Constructor to create new Si114x instance
    *
    * @param sda SDA pin of the I2C interface
    * @param scl SCL pin of the I2C interface
    */
    Si114x(PinName sda, PinName scl);
    
    /* Get the measure visible light intensity
    *
    * @return unsigned short (uint16_t) representing visible light intensity
    */
    unsigned short getVisibleLight(void);
    
    /* Get the measure IR light intensity
    *
    * @return unsigned short (uint16_t) representing IR light intensity
    */
    unsigned short getIRLight(void);
    
    /* Get the measure UV intensity
    *
    * The retval is supposed to be 10 times the UV index. It will be modified
    * to return a float representing the UV index once it doesn't claim
    * the UV index is 50 outside. 
    *
    * @return unsigned short (uint16_t) representing UV intensity
    */
    unsigned short getUVIndex(void);
    
    /* Perform a proximity measurement
    *
    * This enabled LEDs (set using setPSLEDs) and performs a 
    * reflection measurement. It can be used to obtain (relative)
    * proximity, but also to measure for example heartbeat, as in 
    * the HelloWorld program.
    *
    * Currently the code does not substract ambient light (todo)
    *
    * @param pschannel channel to use for the measurement (1-2)
    * @return unsigned short (uint16_t) representing the reflection
    */
    unsigned short getProximity(char pschannel);

    unsigned short getCouleur(void);
    
    /* Set the LEDs for a given proximity measurement
    *
    * The Si1146 has two channels to do measurements with and can control 2 LEDs.
    * This function is used to set which LEDs are used for which channel.
    * Multiple LEDs can be active at the same time. By default the
    * constructor sets LED1 to be active with channel 1 and LED2 to
    * be active with channel 2.
    *
    * @param pschannel channel to set active LEDs for (1-2)
    * @param ledmask LEDs to be active for the set channel (bit 0 is LED1, bit1 is LED2)
    */
    void setPSLEDs(char pschannel, char ledmask);
    
    /* Verify I2C communication can occur with the sensor
    *
    * @return true when the sensor is found
    */
    bool verifyConnection(void);
    
    protected:
    char read_byte(const char reg);
    unsigned short read_word(const char reg);
    void write_byte(const char reg, const char byte);
    void param_set(const char param, const char value);
    char param_query(const char param);
    void write_cmd(const char cmd);
    
    I2C i2c;
    
    bool continious;
    };

#endif
