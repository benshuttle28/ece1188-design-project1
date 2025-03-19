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
#define farLeftTurn     &FSM[1]
#define leftTurn        &FSM[2]
#define leftCenter  &FSM[3]
#define rightCenter &FSM[4]
#define rightTurn       &FSM[5]
#define farRightTurn    &FSM[6]
#define rightAdjustment     &FSM[7]
#define leftAdjustment  &FSM[8]
#define backward        &FSM[9]

#define centerDuty          1000
#define lightTurnDuty       1000
#define hardTurnDuty        2000
#define backwardTurnDuty    1000
#define adjustmentDuty      1000

state_t FSM[10] = {
                  {0x00, centerDuty, centerDuty, {farRightTurn, leftAdjustment, center, center, rightAdjustment, center, backwards, center}},
                  {0x01, backwardTurnDuty, hardTurnDuty, {farLeftTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, rightTurn, backwards, center}},
                  {0x02, 0x00, lightTurnDuty, {farLeftTurn, farLeftTurn, leftCenter, rightTurn, farRightTurn, rightTurn, backwards, center}},
                  {0x03, lightTurnDuty, lightTurnDuty, {farLeftTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, center, backwards, center}},
                  {0x04, lightTurnDuty, lightTurnDuty, {farRightTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, center, backwards, center}},
                  {0x05, lightTurnDuty, 0x00, {farRightTurn, farLeftTurn, leftTurn, rightCenter, farRightTurn, leftTurn, backwards, center}},
                  {0x06, hardTurnDuty, backwardTurnDuty, {farRightTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, leftTurn, backwards, center}},
                  {0x07, 0x00, adjustmentDuty, {farLeftTurn, leftTurn, center, center, farRightTurn, center, backwards, center}},
                  {0x08, adjustmentDuty, 0x00, {farRightTurn, leftTurn, center, center, farRightTurn, center, backwards, center}},
                  {0x09, backwardTurnDuty, backwardTurnDuty, {backwards, farLeftTurn, farLeftTurn, farRightTurn, farRightTurn, farRightTurn, backwards, center}}
                  };

/*

state_t FSM[8] = {
                  {0x00, centerDuty, centerDuty, {farRightTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, center, backwards, center}},
                  {0x01, backwardTurnDuty, hardTurnDuty, {farLeftTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, rightTurn, backwards, center}},
                  {0x02, 0x00, lightTurnDuty, {farLeftTurn, farLeftTurn, leftCenter, rightTurn, farRightTurn, rightTurn, backwards, center}},
                  {0x03, lightTurnDuty, lightTurnDuty, {farLeftTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, center, backwards, center}},
                  {0x04, lightTurnDuty, lightTurnDuty, {farRightTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, center, backwards, center}},
                  {0x05, lightTurnDuty, 0x00, {farRightTurn, farLeftTurn, leftTurn, rightCenter, farRightTurn, leftTurn, backwards, center}},
                  {0x06, hardTurnDuty, backwardTurnDuty, {farRightTurn, farLeftTurn, leftTurn, rightTurn, farRightTurn, leftTurn, backwards, center}},
                  {0x07, backwardTurnDuty, backwardTurnDuty, {backwards, farLeft, farLeft, farRight, farRight, farRight, backwards}}
                  };

/*

state_t FSM[8] = {
                  {0x00, centerDuty, centerDuty, {farRight, farLeftTurn, leftTurn, right, farRight, center, backwards, center}},
                  {0x01, hardTurnDuty, backwardTurnDuty, {right, farLeft, left, right, farRight, leftCenter, backwards, center}},
                  {0x02, lightTurnDuty, 0x00, {farLeft, farLeft, leftCenter, right, farRight, right, backwards, center}},
                  {0x03, centerDuty, centerDuty, {farLeft, farLeft, left, right, farRight, leftCenter, backwards, center}},
                  {0x04, centerDuty, centerDuty, {farRight, farLeft, left, right, farRight, rightCenter, backwards, center}},
                  {0x05, 0x00, lightTurnDuty, {farRight, farLeft, left, rightCenter, farRight, left, backwards, center}},
                  {0x06, backwardTurnDuty, hardTurnDuty, {left, farLeft, left, right, farRight, rightCenter, backwards, center}},
                  {0x07, backwardTurnDuty, backwardTurnDuty, {backwards, farLeft, farLeft, farRight, farRight, farRight, backwards}}
                  };







#endif /* INC_MOTORFSM2_H_ */
