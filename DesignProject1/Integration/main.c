#include "msp.h"
#include <stdint.h>
#include "..\inc\Clock.h"
#include "..\inc\Reflectance.h"
#include "..\inc\MotorSimple.h"
#include "..\inc\MotorFSM.h"

void main() {

    Clock_Init48MHz();
    Motor_InitSimple();

    state_t *motor_pt;
    uint8_t reflectance_input;
    motor_pt = center;
    while(1) {
        // drive motors at given duty cycles
        reflectance_input = Reflectance_Center(1000);
        motor_pt = motor_pt->next[reflectance_input];

    }

}
