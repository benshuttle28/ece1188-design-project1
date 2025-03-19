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

void Illuminate_LEDs(uint8_t sensor_out) {
    P2->OUT &= ~0x07;
    if (sensor_out == 0x00) {
        P2->OUT |= 0x01; // red, straight
    }
    else if (sensor_out == 0x01) {
        P2->OUT |= 0x04; // blue, far left turn
    }
    else if (sensor_out == 0x02) {
        P2->OUT |= 0x02; // green, left turn
    }
    else if (sensor_out == 0x03) {
        P2->OUT |= 0x02; // green, left turn
    }
    else if (sensor_out == 0x04) {
        P2->OUT |= 0x03; // yellow, right turn
    }
    else if (sensor_out == 0x05) {
        P2->OUT |= 0x03; // yellow, right turn
    }
    else if (sensor_out == 0x06) {
        P2->OUT |= 0x07; // white, hard right turn
    }
    else {
        P2->OUT |= 0x05; // pink, other
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

