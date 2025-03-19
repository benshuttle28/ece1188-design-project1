#include <stdint.h>
#include "..\inc\Reflectance.h"


uint8_t Reflectance_Center_int(uint8_t data){
    // write this as part of Lab 6
    int32_t distance = Reflectance_Position(data);
    if (data == 0x00) {
        return 0x00;
    }
    else if (distance > 0) {
        return 0x01;
    }
    else if (distance < 0) {
        return 0x02;
    }
    else if ((distance >= -4800) && (distance <= 4800)) {
        return 0x03;
    }

        return 0x00;
    }

int w[8] = {-33400,-23800,-14300,-4800,4800,14300,23800,33400};

uint8_t Reflectance_Center_int2(uint8_t data) {
    int32_t distance = Reflectance_Position(data);
    if (data == 0x00) {
        return 0x00;
    }

    // positive = off to the right
    else if (distance >= 33400) {
        return 0x01; // far off to right
    }
    else if ((distance > 4800) && (distance < 33400)) {
        return 0x02; // off to right
    }
    else if ((distance < -4800) && (distance > -33400)) {
        return 0x03; // off to left
    }
    else if (distance <= -33400) {
        return 0x04; // far off to left
    }
    else if ((distance >= -4800) && (distance <= 4800)) {
        return 0x05; // centered
    }

    return 0x00;
}
