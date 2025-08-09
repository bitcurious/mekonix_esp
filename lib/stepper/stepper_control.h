#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H


#include <Arduino.h>

// Motor 1 connections
#define DIR_PIN 27
#define PULSE_PIN 26

// Motor 2 connections
#define DIR_PIN_M2 16
#define PULSE_PIN_M2 17

//Relay pin
#define RELAY_PIN 33

//Home position pins
#define HOME_M1 34
#define HOME_M2 35

// Define run times for motors
// Adjust these values as needed
#define RUN_TIME 500  // Time in milliseconds
#define RUN_TIME_M1 450 //time in milliseconds for motor 1

// #define LED_BUILTIN 2

void steper_motor_setup();
void runMotors(unsigned long duration, unsigned long startTime);
void stepper_loop();
bool go_to_home_position();


#endif

