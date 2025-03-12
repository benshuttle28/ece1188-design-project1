#include "msp.h"
#include <stdint.h>
#include "..\inc\Clock.h"
#include "..\inc\TExaS.h"
#include "..\inc\CortexM.h"
#include "..\inc\SysTick.h"
#include "..\inc\LaunchPad.h"
#include "MotorFSM.h"

void main() {

    Clock_Init48MHz();
    Motor_InitSimple();

    state_t *motor_pt;
    uint8_t reflectance_input;
    motor_pt = center;
    while(1) {
        // drive motors at given duty cycles
        reflectance_input = Reflectance_Center(1000);
        pt = pt->next[reflectance_input];

    }

}
