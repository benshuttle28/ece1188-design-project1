// Lab13_Timersmain.c
// Runs on MSP432
// Student starter code for Timers lab

// PWM output to motor
// Second Periodic interrupt
// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

// Left motor direction connected to P5.4 (J3.29)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P5.5 (J3.30)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)

#include "msp.h"
#include "Bump.h"
#include "Clock.h"
#include "SysTick.h"
#include "CortexM.h"
#include "LaunchPad.h"
#include "Motor.h"
#include "TimerA1.h"
#include "TExaS.h"

// Driver test
void TimedPause(uint32_t time)
{
    Clock_Delay1ms(time);          // run for a while and stop
    Motor_Stop();
    while (LaunchPad_Input() == 0)
        ;  // wait for touch
    while (LaunchPad_Input())
        ;     // wait for release
}
int Program13_1(void)
{
    Clock_Init48MHz();
    LaunchPad_Init(); // built-in switches and LEDs
    Bump_Init();      // bump switches
    Motor_Init();     // your function
    while (1)
    {
        Clock_Delay1ms(1000);
        Motor_Forward(1000, 1000);  // your function
        Clock_Delay1ms(1000);
        Motor_Backward(2000, 2000); // your function
        Clock_Delay1ms(1000);
        Motor_Left(2000, 1000);     // your function
        Clock_Delay1ms(1000);
        Motor_Right(2000, 1000);    // your function
        Clock_Delay1ms(1000);
        Motor_Stop();
    }
}

// Test of Periodic interrupt
#define REDLED (*((volatile uint8_t *)(0x42098060)))
#define BLUELED (*((volatile uint8_t *)(0x42098068)))
uint32_t Time;
void Task(void)
{
    Time = Time + 1;
    if (Time % 100 == 0)
    {
        P2->OUT ^= 0x04;
    }
}

//int Program13_2(void)
//{
//    Clock_Init48MHz();
//    LaunchPad_Init();  // built-in switches and LEDs
//    uint32_t time = 50000;
//    TimerA1_Init(&Task, time);  // 1000 Hz
//    EnableInterrupts();
//    while (1)
//    {
//        ; // toggle P2.1
//    }
//}

int main(void)
{
    // write a main program that uses PWM to move the robot
    // like Program13_1, but uses TimerA1 to periodically
    // check the bump switches, stopping the robot on a collision

    Program13_1();

}
