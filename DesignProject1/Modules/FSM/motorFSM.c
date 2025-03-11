#include "msp.h"
#include <stdint.h>
#include "..\inc\Clock.h"
#include "..\inc\TExaS.h"
#include "..\inc\CortexM.h"
#include "..\inc\SysTick.h"
#include "..\inc\LaunchPad.h"

struct motorState {
    uint8_t out;
    uint16_t leftDuty;
    uint16_t rightDuty;
    const struct motorState *next[4];
};

typedef const struct motorState state_t;
#define center      &FSM[0]
#define left        &FSM[1]
#define leftCenter  &FSM[2]
#define right       &FSM[3]
#define rightCenter &FSM[4]

#define CenterDuty      0
#define hardTurnDuty    0
#define lightTurnFast   0
#define lightTurnSlow   0

state_t FSM[5] = {
                  {0x00, centerDuty, centerDuty, {right, left, right, center}},
                   {0x01, hardTurnDuty, 0x00, {left, leftCenter, right, left}},
                    {0x02, centerDuty, centerDuty, {left, left, right, leftCenter}},
                     {0x03, 0x00, hardTurnDuty, {right, left, rightCenter, right}},
                      {0x04, 0x00, centerDuty, centerDuty, {right, left, right, rightCenter}}

};


