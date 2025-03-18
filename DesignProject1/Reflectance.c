// reflectance even LED illuminate connected to P5.3
// reflectance odd LED illuminate connected to P9.2
// reflectance sensor 1 connected to P7.0 (robot's right, robot off road to left)
// reflectance sensor 2 connected to P7.1
// reflectance sensor 3 connected to P7.2
// reflectance sensor 4 connected to P7.3 center
// reflectance sensor 5 connected to P7.4 center
// reflectance sensor 6 connected to P7.5
// reflectance sensor 7 connected to P7.6
// reflectance sensor 8 connected to P7.7 (robot's left, robot off road to right)

#include <stdint.h>
#include "msp432.h"
#include "Clock.h"

// ------------Reflectance_Init------------
// Initialize the GPIO pins associated with the QTR-8RC
// reflectance sensor.  Infrared illumination LEDs are
// initially off.
// Input: none
// Output: none
void Reflectance_Init(void)
{
    // setup CTRL EVEN on P5.3
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08; // P5.3 setup as GPIO
    P5->DIR |= 0x08; // P5.3 setup as output
    P5->OUT &= ~0x08; // turn LEDs off initially

    // setup CTRL ODD on P9.2
    P9->SEL0 &= ~0x04;
    P9->SEL1 &= ~0x04; // P9.2 setup as GPIO
    P9->DIR |= 0x04; // P9.2 setup as output
    P9->OUT &= ~0x04; // turn LEDs off initially

    // setup QTRX sensor
    P7->SEL0 &= ~0x00;
    P7->SEL1 &= ~0x00; // P7.0 through P7.7 setup as GPIO
    P7->DIR &= ~0x00; // P7.0 through P7.7 setup as input
}

// ------------Reflectance_Read------------
// Read the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Read(uint32_t time)
{
    uint8_t result;

    P5->OUT |= 0x08; // turn on even LEDs
    P9->OUT |= 0x04; // turn on odd LEDs

    P7->DIR = 0xFF; // set P7.7 through P7.0 to output
    P7->OUT = 0xFF; // charge the capacitors

    Clock_Delay1us(10); // wait 10 microseconds for cap charging to finish

    P7->DIR = 0x00; // change P7.7 through P7.0 to input

    Clock_Delay1us(time); // wait for time in microseconds

    result = P7->IN & 0xFF; // read the sensor voltages (only last 8 bits of P7)

    P5->OUT &= ~0x08; // turn off even LEDs
    P9->OUT &= ~0x04; // turn off odd LEDs

    return result;
}

// ------------Reflectance_Center------------
// Read the two center sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: 0 (off road), 1 off to left, 2 off to right, 3 on road
// (Left,Right) Sensors
// 1,1          both sensors   on line
// 0,1          just right     off to left
// 1,0          left left      off to right
// 0,0          neither        lost
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Center(uint32_t time)
{
    uint8_t result;

    P5->OUT |= 0x08; // turn on even LEDs
    P9->OUT |= 0x04; // turn on odd LEDs

    P7->DIR = 0xFF; // set P7.7 through P7.0 to output
    P7->OUT = 0xFF; // charge the capacitors

    Clock_Delay1us(10);

    P7->DIR = 0x00; // change P7.7 through P7.0 to input

    Clock_Delay1us(time);

    result = P7->IN & 0x18; // read the sensor voltages (only bits 3 and 4)

    P5->OUT &= ~0x08; // turn off even LEDs
    P9->OUT &= ~0x04; // turn off odd LEDs

    return result;
}

// Perform sensor integration
// Input: data is 8-bit result from line sensor
// Output: position in 0.1mm relative to center of line
int32_t Reflectance_Position(uint8_t data)
{
    int32_t w[8] = { -33400, -23800, -14300, -4800, 4800, 14300, 23800, 33400 };

    int32_t numerator = 0;
    int32_t denominator = 0;
    int32_t i;

    for (i = 0; i < 8; i++)
    {
        // using !! to convert any non-zero value to 1
        int32_t bit_value = !!(data & (1 << i));
        numerator += bit_value * w[i];
        denominator += bit_value;
    }

    if (denominator == 0)
        return 0;  // Prevent division by zero
    return (numerator / denominator);
}

// ------------Reflectance_Start------------
// Begin the process of reading the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// Input: none
// Output: none
// Assumes: Reflectance_Init() has been called
void Reflectance_Start(void)
{
    // turn on 8 IR LEDs by setting P5.3 and P9.2 high
    P5->OUT |= 0x08;
    P9->OUT |= 0x04;

    // Make P7.7-P7.0 outputs, set all high
    P7->DIR = 0xFF;
    P7->OUT = 0xFF;

    // wait 10 microseconds
    Clock_Delay1us(10);

    // Make P7.7-P7.0 inputs
    P7->DIR &= ~0xFF;
}

// ------------Reflectance_End------------
// Finish reading the eight sensors
// Read sensors
// Turn off the 8 IR LEDs
// Input: none
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
// Assumes: Reflectance_Start() was called 1 ms ago
uint8_t Reflectance_End(void)
{
    // read the 8-bit sensor result
    uint8_t result = P7->IN;

    // turn off the 8 IR LEDs
    P7->OUT = ~0xFF;

    return result;
}

