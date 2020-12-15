#ifndef MAIN_H
#define MAIN_H

#include "mbed.h"
#include "LIS3DSH.h"
#include "LEDBLINK.h"
#include "USBSerial.h"
#include "FILTER.h"
#include "SITUP.h"

#define LED_LIGHT_MASK 0x0000F000
#define LED_SHUTDOWN_MASK 0x00000000
#define MAX_COUNT 5
#define MAX_DEGREE 5


/**** define 4 kinds of exercises state ****/
typedef enum {
  SITUPS,
  PUSHUPS,
  JUMPINGJACKS,
  SQUATS
} WORKOUT;

/**** Variables ****/
int16_t X, Y, Z; 
float angle, pitch, filter_angle;
volatile bool resetFlag = false;
volatile int switchExercise = 0;

/**** init objects ****/
LEDBLINK ledControl;
USBSerial logger;
Timer debounce;
Ticker ticker;
LIS3DSH acc(PA_7, PA_6, PA_5, PE_3); // accelerometer
PortOut portD(PortD); // 13 12 14 15  PD 0~15  
InterruptIn button(BUTTON1);
FILTER filter;


SITUP sp(&X, &Y, &Z, &angle, &switchExercise);


/**** button Interrupt routine - is interrupt activated by a falling edge of button input ****/
void changeExercise (void) {
    if (debounce.read_ms()>20) {
      switchExercise = (switchExercise + 1) % 4;
    }
    debounce.reset(); 
}


/**** use ticker to deal with angle  ****/
void getACCData()
{
  acc.ReadData(&X, &Y, &Z);
  acc.ReadAngles(&angle, &pitch); 
  angle = filter.filterAngle(Z);
}


/**** Prepare Before Loop  ****/
void prepareBeforeLoop() {
  // ledControl.blinkCircle(1); 
  debounce.start();
  button.fall(&changeExercise);
  ticker.attach(&getACCData, 0.1); //10hz
  sp.setLogger(&logger);
}

void detect(EXEC* exec, int max_count, WORKOUT curExec, float delay, int port) {
  // exec->indicate(12, .5);
  exec->count = 0;
  while (exec->count < max_count && switchExercise == curExec) {
    exec->detect();

    wait(delay);
    if(switchExercise != curExec) {
      exec->reset();
      break; 
    }
    wait(delay);
    portD = 1U<<port; // green
  }
  
  if (exec->count == max_count) {
    exec->reset();
    exec->finish();
  }
}




#endif