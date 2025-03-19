#include "msp.h"
#include <stdint.h>
#include "Clock.h"
#include "Motor.h"
#include "../Modules/BumpSwitches/Bump.h"
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
uint8_t bumpReading;

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
    else {
        P2->OUT &= ~0x02;
        P2->OUT |= 0x05; // pink, other
    }
}

void SysTick_Handler(void){ // every 1ms
  if ((interrupts % 10) == 0) {
      reflectance_lock = 1;
      Reflectance_Start();
  }
  else if ((interrupts % 10) == 1) {
      bumpReading = Bump_Read();

      //if(bumpReading == 0){
      sensor_out = Reflectance_End();
      reflectance_lock = 0;
      reflectance_input = Reflectance_Center_int2(sensor_out);
      motor_pt = motor_pt->next[reflectance_input];
      // drive motors at given duty cycles
      if(motor_pt->out == 0x01){
          Motor_Left(motor_pt->leftDuty, motor_pt->rightDuty); // left turn
      }
      else if(motor_pt->out == 0x06){
          Motor_Right(motor_pt->leftDuty, motor_pt->rightDuty); // right turn
      }
      else {
      Motor_Forward(motor_pt->leftDuty, motor_pt->rightDuty);
      }
      out = motor_pt->out;
      Illuminate_LEDs(out);
      //}
//      else {
//          // some bump switches hit
//          if(bumpReading == 0x44){
//              // center switches
//              Motor_Backward(2000, 2000);
//              Clock_Delay1ms(1500);
//          } else if(bumpReading == 0xC0 || bumpReading == 0x80 || bumpReading == 0x40){
//              // left swtiches (turn left then back up)
//              Motor_Backward(2000, 2000);
//              Clock_Delay1ms(1000);
//              Motor_Left(2000, 2000);
//              Clock_Delay1ms(500);
//
//          } else if(bumpReading == 0x01 || bumpReading == 0x02 || bumpReading == 0x03)
//              // right switches (turn right then back up)
//              Motor_Backward(2000, 2000);
//              Clock_Delay1ms(1000);
//              Motor_Right(2000, 2000);
//              Clock_Delay1ms(500);
//      }

  }
  interrupts += 1;
}

void Pause(void){
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}

void main() {

    Clock_Init48MHz();
    LaunchPad_Init();
    //Pause();
    Motor_Init();
    Reflectance_Init();
    SysTick_Init(48000, 1);
    EnableInterrupts();

    motor_pt = center;



    while(1) {


    }

}
