#include "msp.h"
#include <stdint.h>
#include "Clock.h"
#include "Motor.h"
#include "Reflectance.h"
#include "LaunchPad.h"
#include "SysTickInts.h"
#include "CortexM.h"
#include "MotorFSM.h"
#include "../Modules/FSM/fsm.h"


uint8_t out;
uint8_t reflectance_input;
state_t *motor_pt;
uint8_t reflectance_lock = 0;
uint8_t interrupts = 0;
uint8_t sensor_out;


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
      Motor_Forward(motor_pt->leftDuty, motor_pt->rightDuty);
      out = motor_pt->out;
      //Illuminate_LEDs(sensor_out);


  }
  interrupts += 1;
}

void Pause(void){
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}

void main() {

    Clock_Init48MHz();
    Motor_Init();
    LaunchPad_Init();
    Reflectance_Init();
    SysTick_Init(48000, 1);
    EnableInterrupts();

    motor_pt = center;



    while(1) {
        Pause();

    }

}
