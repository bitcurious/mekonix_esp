#include "stepper_control.h"



void steper_motor_setup() {
    /// Motor 1
    pinMode(DIR_PIN, OUTPUT);
    pinMode(PULSE_PIN, OUTPUT);

    // Motor 2
    pinMode(DIR_PIN_M2, OUTPUT);
    pinMode(PULSE_PIN_M2, OUTPUT);

    //Relay
    pinMode(RELAY_PIN, OUTPUT);
    //led
    // pinMode(LED_BUILTIN, OUTPUT);
}

// Function to run motors for the specified time
void run_motor_1(unsigned long duration, unsigned long startTime) {
    // unsigned long startTime = millis();  // Record start time
    
    while (millis() - startTime < duration) {  // Run for specified time
        digitalWrite(PULSE_PIN, HIGH);
        // digitalWrite(PULSE_PIN_M2, HIGH);
        delayMicroseconds(150);  // Adjust for your stepper driver
        digitalWrite(PULSE_PIN, LOW);
        // digitalWrite(PULSE_PIN_M2, LOW);
        delayMicroseconds(150);
    }
}

void run_motor_2(unsigned long duration, unsigned long startTime) {
    // unsigned long startTime = millis();  // Record start time
    
    while (millis() - startTime < duration) {  // Run for specified time
        // digitalWrite(PULSE_PIN, HIGH);
        digitalWrite(PULSE_PIN_M2, HIGH);
        delayMicroseconds(150);  // Adjust for your stepper driver
        // digitalWrite(PULSE_PIN, LOW);
        digitalWrite(PULSE_PIN_M2, LOW);
        delayMicroseconds(150);
    }
    
}


void stepper_loop(float pose_x) {

    pose_x = constrain(pose_x, 0, 640);
    
    // Map RUN_TIME: 0→0, 320→250, 640→500
    float run_time_m1 = map(pose_x, 0, 640, 0, 500);
    
    // Map RUN_TIME_M1: 0→500, 320→250, 640→0 (inverse of RUN_TIME)
    float run_time_m2 = map(pose_x, 0, 640, 500, 0);
    
    // For debugging:
    Serial.print("X Position: ");
    Serial.print(pose_x);
    Serial.print(" | RUN_TIME_M1: ");
    Serial.print(run_time_m1);
    Serial.print(" | RUN_TIME_M2: ");
    Serial.println(run_time_m2);

    Serial.println("Stepper loop started");
    Serial.println("Picking the object");
    // Move forward motor 1
    digitalWrite(DIR_PIN, LOW);  // Forward direction for Motor 1
    unsigned long startTime = millis();
    run_motor_1(run_time_m1, startTime);

    delay(1000);

    //moving forward motor 2
    digitalWrite(DIR_PIN_M2, HIGH);  // Forward direction for Motor 1
    unsigned long startTime_2 = millis();
    run_motor_2(run_time_m2, startTime_2);
    digitalWrite(RELAY_PIN, HIGH);

    delay(5000);

    // Move backward motor 1
    digitalWrite(DIR_PIN, HIGH);  // Reverse direction for Motor 1
    unsigned long startTime_3 = millis();
    run_motor_1(run_time_m1, startTime_3);
    Serial.println("Object Picked");
    
    delay(1000);

    //moving backward motor 2
    digitalWrite(DIR_PIN_M2, LOW);  // Reverse direction for Motor 1
    unsigned long startTime_4 = millis();
    run_motor_2(run_time_m2, startTime_4);
    Serial.println("Object Picked");
    delay(1000);
    digitalWrite(RELAY_PIN, LOW);

    //led code
    // digitalWrite(LED_BUILTIN, HIGH);  // Turn LED on
    // delay(500);  // Wait 500ms
    // digitalWrite(LED_BUILTIN, LOW);   // Turn LED off
    // delay(500);  // Wait 500ms

    // Serial.println("Stepper loop started");
    // Serial.println("Picking the object");
    // // Move forward motor 1
    // digitalWrite(DIR_PIN, HIGH);  // Forward direction for Motor 1
    // unsigned long startTime = millis();
    // run_motor_1(RUN_TIME_M1, startTime);
    // digitalWrite(RELAY_PIN, HIGH);

    // delay(5000);  // Pause before changing direction

    // // Move backward motor 1
    // digitalWrite(DIR_PIN, LOW);  // Reverse direction for Motor 1
    // unsigned long startTime_2 = millis();
    // run_motor_1(RUN_TIME_M1, startTime_2);
    // Serial.println("Object Picked");
    // delay(1000);
    // Serial.println("Placing the object");
    // // Move forward motor 2
    // digitalWrite(DIR_PIN_M2, LOW); // Forward direction for Motor 2
    // unsigned long startTime_3 = millis();
    // run_motor_2(RUN_TIME, startTime_3);

    // delay(1000);

    // // Move forward motor 1
    // digitalWrite(DIR_PIN_M2, HIGH); // Reverse direction for Motor 2
    // unsigned long startTime_4 = millis();
    // run_motor_2(RUN_TIME, startTime_4);
    // digitalWrite(RELAY_PIN, LOW);
    // Serial.println("Object placed");
    // delay(1000);  // Pause before next cycle
}


    


