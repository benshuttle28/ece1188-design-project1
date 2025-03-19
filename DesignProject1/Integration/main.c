#include "msp.h"
#include <stdint.h>
#include "Clock.h"
#include "Motor.h"
#include "../Modules/BumpSwitches/bump.h"
#include "Reflectance.h"
#include "LaunchPad.h"
#include "SysTickInts.h"
#include "CortexM.h"
#include "MotorFSM.h"
#include "../Modules/FSM/fsm.h"

uint8_t reflectance_input;
state_t *motor_pt;
uint8_t interrupts = 0;
uint8_t sensor_out;
extern volatile uint8_t bumpFlag;

void set_pins() {
    P1->SEL0 &= ~0xFF;
    P1->SEL1 &= ~0xFF;
    P1->DIR |= 0xFF;
    P1->OUT &= ~0xFF;

    P2->SEL0 &= ~0xFF;
    P2->SEL1 &= ~0xFF;
    P2->DIR |= 0xFF;
    P2->OUT &= ~0xFF;

    P3->SEL0 &= ~0xFF;
    P3->SEL1 &= ~0xFF;
    P3->DIR |= 0xFF;
    P3->OUT &= ~0xFF;

    P4->SEL0 &= ~0xFF;
    P4->SEL1 &= ~0xFF;
    P4->DIR |= 0xFF;
    P4->OUT &= ~0xFF;

    P5->SEL0 &= ~0xFF;
    P5->SEL1 &= ~0xFF;
    P5->DIR |= 0xFF;
    P5->OUT &= ~0xFF;

    P6->SEL0 &= ~0xFF;
    P6->SEL1 &= ~0xFF;
    P6->DIR |= 0xFF;
    P6->OUT &= ~0xFF;

    P8->SEL0 &= ~0xFF;
    P8->SEL1 &= ~0xFF;
    P8->DIR |= 0xFF;
    P8->OUT &= ~0xFF;

    P9->SEL0 &= ~0xFF;
    P9->SEL1 &= ~0xFF;
    P9->DIR |= 0xFF;
    P9->OUT &= ~0xFF;

    P10->SEL0 &= ~0xFF;
    P10->SEL1 &= ~0xFF;
    P10->DIR |= 0xFF;
    P10->OUT &= ~0xFF;
}

void SysTick_Handler(void)
{ // every 1ms
    if ((interrupts % 10) == 0)
    {
        Reflectance_Start();
    }
    else if ((interrupts % 10) == 1)
    {
        if (bumpFlag == 0)
        {
            sensor_out = Reflectance_End();
            reflectance_input = Reflectance_Center_int2(sensor_out);
            motor_pt = motor_pt->next[reflectance_input];

            // drive motors at given duty cycles
            if (motor_pt->out == 0x01)
            {
                Motor_Left(motor_pt->leftDuty, motor_pt->rightDuty); // left turn
            }
            else if (motor_pt->out == 0x06)
            {
                Motor_Right(motor_pt->leftDuty, motor_pt->rightDuty); // right turn
            }
            else
            {
                Motor_Forward(motor_pt->leftDuty, motor_pt->rightDuty);
            }
        }
        else
        {
            // some bump switches hit
            if (bumpFlag & 0x0C)
            {
                // center switches
                Motor_Backward(2000, 2000);
                Clock_Delay1ms(1500);
            }
            else if (bumpFlag & 0x30)
            {
                // left swtiches (turn left then back up)
                Motor_Backward(2000, 2000);
                Clock_Delay1ms(1000);
                Motor_Left(2000, 2000);
                Clock_Delay1ms(500);

            }
            else if (bumpFlag & 0x03)
            {
                // right switches (turn right then back up)
                Motor_Backward(2000, 2000);
                Clock_Delay1ms(1000);
                Motor_Right(2000, 2000);
                Clock_Delay1ms(500);
            }
            Reset_Flag();
        }

    }
    interrupts += 1;
}

void main()
{

    Clock_Init48MHz();
    set_pins();
    LaunchPad_Init();
    Bump_Init();
    Motor_Init();
    Reflectance_Init();
    SysTick_Init(48000, 1);
    EnableInterrupts();

    motor_pt = center;

    while (1)
    {

    }

}
