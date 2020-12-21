#ifndef JUMPINGJACK_H
#define JUMPINGJACK_H
 
#include "mbed.h"
#include "USBSerial.h"
#include "EXEC.h"

class JUMPINGJACK: public EXEC {
    public:
        JUMPINGJACK(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise);
        virtual void detect();

        typedef enum {
        standing,
        jumping
        } state;
        state s = standing;
};  
#endif



