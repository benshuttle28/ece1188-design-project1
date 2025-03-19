#include "msp.h"
#include <stdint.h>
#include "..\inc\Clock.h"
#include "..\inc\Reflectance.h"
#include "..\inc\TExaS.h"
#include "..\inc\SysTickInts.h"
#include "..\inc\CortexM.h"
#include "..\inc\MotorFSM.h"
#include "..\Modules\FSM\fsm.h"


uint8_t out;
uint8_t reflectance_input;
state_t *motor_pt;
uint8_t reflectance_lock = 0;
uint8_t interrupts = 0;
uint8_t sensor_out;

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

void Illuminate_LEDs(uint8_t sensor_out) {
    if (sensor_out == 0x00) {
        P2->OUT &= ~0x06;
        P2->OUT |= 0x01; // red, straight
    }
    else if (sensor_out == 0x01) {
        P2->OUT &= ~0x03;
        P2->OUT |= 0x04; // blue, far left turn
    }
    else if (sensor_out == 0x02) {
        P2->OUT &= ~0x05;
        P2->OUT |= 0x02; // green, left turn
    }
    else if (sensor_out == 0x03) {
        P2->OUT &= ~0x05;
        P2->OUT |= 0x02; // green, left turn
    }
    else if (sensor_out == 0x04) {
        P2->OUT &= ~0x04;
        P2->OUT |= 0x03; // yellow, right turn
    }
    else if (sensor_out == 0x05) {
        P2->OUT &= ~0x04;
        P2->OUT |= 0x03; // yellow, right turn
    }
    else if (sensor_out == 0x06) {
        P2->OUT &= ~0x00;
        P2->OUT |= 0x07; // white, hard right turn
    }
    else if (sensor_out == 0x07 ){
        P2->OUT &= ~0x02;
        P2->OUT |= 0x05; // pink, left adjustment
    }
    else if (sensor_out == 0x08) {
        P2->OUT &= ~0x01;
        P2->OUT |= 0x06; // sky blue
    }
}


void SysTick_Handler(void){ // every 1ms
  if ((interrupts % 10) == 0) {
      reflectance_lock = 1;
      Reflectance_Start();
  }
  else if ((interrupts % 10) == 1) {
      sensor_out = Reflectance_End();
      reflectance_lock = 0;
      reflectance_input = Reflectance_Center_int(sensor_out);
      motor_pt = motor_pt->next[reflectance_input];
      // drive motors at given duty cycles
      out = motor_pt->out;
      Illuminate_LEDs(out);


  }
  interrupts += 1;
}

void main() {

    Clock_Init48MHz();
    //Motor_InitSimple();
    Reflectance_Init();
    SysTick_Init(48000, 1);
    EnableInterrupts();

    motor_pt = center;



    while(1) {




    }

}

