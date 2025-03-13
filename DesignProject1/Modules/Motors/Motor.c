#include <stdint.h>
#include "msp.h"
#include "CortexM.h"
#include "PWM.h"

//**************RSLK1.1***************************
// Left motor direction connected to P5.4 (J3.29)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P5.5 (J3.30)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)
// *******Lab 13 solution*******

void Motor_Init(void)
{
// Initializes the 6 GPIO lines and puts driver to sleep
// Returns right away

// initialize P5.4 and P5.5 and make them outputs
// set P5.5 (right motor direction) and P5.4 (left motor direction) to GPIO
    P5->SEL0 &= ~0x30; // 0b110000
    P5->SEL1 &= ~0x30;

// set P3.6 (right motor sleep) and P3.7 (left motor sleep) to GPIO
    P3->SEL0 &= ~0xC0; // 0b11000000
    P3->SEL1 &= ~0xC0;

// set P2.6 (right motor PWM) and P2.7 (left motor PWM) to GPIO
    P2->SEL0 &= ~0xC0; // 0b11000000
    P2->SEL1 &= ~0xC0;

// set direction registers
    P5->DIR |= 0x30; // P5.5 and P5.4 set to output (0b110000)
    P3->DIR |= 0xC0; // P3.6 and P3.7 set to output (0b11000000)
    P2->DIR |= 0xC0; // P2.6 and P2.7 set to output (0b11000000)

// set output of motor pins to zero so motors stopped after initialization
    P3->OUT &= ~0xC0;
    P2->OUT &= ~0xC0;

// setup system timer
    PWM_Init34(10000, 5000, 5000);
}

void Motor_Stop(void)
{
// Stops both motors, puts driver to sleep
// Returns right away
    P1->OUT &= ~0xC0;
    P2->OUT &= ~0xC0;   // off
    P3->OUT &= ~0xC0;   // low current sleep mode
    P3->OUT |= 0xC0;
}

void Motor_Forward(uint16_t leftMotorDuty, uint16_t rightMotorDuty)
{
// left motor forward
    P5->OUT &= ~0x10; // Set P5.4 PH to zero (forward)
    P3->OUT |= 0x80; // set P3.7 nSleep to 1

// right motor forward
    P5->OUT &= ~0x20; // Set P5.5 PH to zero (forward)
    P3->OUT |= 0x40; // Set P3.6 nSleep to 1

    PWM_Duty3(rightMotorDuty);
    PWM_Duty4(leftMotorDuty);
}

void Motor_Backward(uint16_t leftMotorDuty, uint16_t rightMotorDuty)
{
// Drives both motors backward at duty (0 to 14,998)
    // left motor backward
    P5->OUT |= 0x10; // Set P5.4 PH to 1 for backward movement
    P3->OUT |= 0x80; // Set P3.7 nSleep to 1

    // right motor backward
    P5->OUT |= 0x20; // Set P5.5 PH to 1 for backward movement
    P3->OUT |= 0x40; // Set P3.6 nSleep to 1

    PWM_Duty3(rightMotorDuty);
    PWM_Duty4(leftMotorDuty);

}

void Motor_Left(uint16_t leftMotorDuty, uint16_t rightMotorDuty)
{
    // Drives the left motor backward at duty (0 to 14,998)
    // Drives the right motor forward at duty (0 to 14,998)

    // left motor backward
    P5->OUT |= 0x10; // Set P5.4 PH to 1 for backward movement
    P3->OUT |= 0x80; // Set P3.7 nSleep to 1

    // right motor forward
    P5->OUT &= ~0x20; // Set P5.5 PH to 0 for forward movement
    P3->OUT |= 0x40; // Set P3.6 nSleep to 1

    PWM_Duty3(rightMotorDuty);
    PWM_Duty4(leftMotorDuty);
}

void Motor_Right(uint16_t leftMotorDuty, uint16_t rightMotorDuty)
{
// Drives the right motor backward at duty (0 to 14,998)
// Drives the left motor forward at duty (0 to 14,998)

    // left motor forward
    P5->OUT &= ~0x10; // Set P5.4 PH to 0 for forward movement
    P3->OUT |= 0x80; // Set P3.7 nSleep to 1

    // right motor backward
    P5->OUT |= 0x20; // Set P5.5 PH to 1 for backward movement
    P3->OUT |= 0x40; // Set P3.6 nSleep to 1

    PWM_Duty3(rightMotorDuty);
    PWM_Duty4(leftMotorDuty);
}
