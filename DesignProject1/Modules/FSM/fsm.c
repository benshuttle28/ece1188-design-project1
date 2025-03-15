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
    else if (distance == 0) {
        return 0x03;
    }

        return 0x00;
    }
