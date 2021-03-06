#include "PUSHUP.h"
#include <math.h> 
PUSHUP::PUSHUP(int16_t* X, int16_t* Y, int16_t* Z, float* angle, volatile int* switchExercise):EXEC(X, Y, Z, angle, switchExercise) {
}

void PUSHUP::detect() {
    // detect
    switch (s)
    {
    case up:
      if (*ag > 160) {
        state_count++;
        s = down;
        *pd = 0U<<13; // green
        indicate(13, 0.2);
      }
      break;
    case down:
      if (*ag < 147) {
        state_count++;
        s = up;
        *pd = 1U<<13; // green
        indicate(13, 0.2);
      }
    default:
      break;
    }
    if (state_count == 2) {
      total_count++;
      state_count = 0;
    }
    log->printf("total_count: %d, angle: %f  \n", total_count, *ag);
}



