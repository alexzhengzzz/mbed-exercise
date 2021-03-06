#ifndef SITUP_H
#define SITUP_H
 
#include "mbed.h"
#include "USBSerial.h"
#include "EXEC.h"

class SITUP : public EXEC {
    public:
        SITUP(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise);
        virtual void detect();
       
        typedef enum {
        lying,
        sitting
        } state;
        state s = lying;
};  
#endif



