/*
 * MotorFSM2.h
 *
 *  Created on: Mar 15, 2025
 *      Author: joeln
 */

#ifndef INC_MOTORFSM2_H_
#define INC_MOTORFSM2_H_

struct motorState {
    uint8_t out;
    uint16_t leftDuty;
    uint16_t rightDuty;
    const struct motorState *next[8];
};

typedef const struct motorState state_t;
#define center      &FSM[0]
#define farLeft     &FSM[1]
#define left        &FSM[2]
#define leftCenter  &FSM[3]
#define rightCenter &FSM[4]
#define right       &FSM[5]
#define farRight    &FSM[6]
#define backwards     &FSM[7]

#define centerDuty          1000
#define lightTurnDuty       1000
#define hardTurnDuty        2000
#define backwardTurnDuty    -1000

state_t FSM[8] = {
                  {0x00, centerDuty, centerDuty, {farRight, farLeft, left, right, farRight, leftCenter, backwards, center}},
                  {0x01, hardTurnDuty, backwardTurnDuty, {right, farLeft, left, right, farRight, leftCenter, backwards, center}},
                  {0x02, lightTurnDuty, 0x00, {farLeft, farLeft, leftCenter, right, farToRight, left, backwards, center}},
                  {0x03, centerDuty, centerDuty, {farLeft, farLeft, left, right, farRight, leftCenter, backwards, center}},
                  {0x04, centerDuty, centerDuty, {farRight, farLeft, left, right, farRight, rightCenter, backwards, center}},
                  {0x05, 0x00, lightTurnDuty, {farRight, farLeft, left, rightCenter, farRight, right, backwards, center}},
                  {0x06, backwardTurnDuty, hardTurnDuty, {left, farLeft, left, right, farRight, rightCenter, backwards, center}},
                  {0x07, backwardTurnDuty, backwardTurnDuty, {backwards, farLeft, farLeft, farRight, farRight, farRight, backwards}}
                  };


};




#endif /* INC_MOTORFSM2_H_ */
