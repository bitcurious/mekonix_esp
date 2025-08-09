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

bool go_to_home_position() {

    int adcValue = analogRead(HOME_M1); // raw ADC value (0-4095)
    int adcValue1 = analogRead(HOME_M2); // raw ADC value (0-4095)
    // Convert to voltage (ESP32 default ADC reference = 3.3V)
    float voltage = adcValue * (3.3 / 4095.0);
    float voltage1 = adcValue1 * (3.3 / 4095.0);

    Serial.print("ADC Value: ");
    Serial.print(adcValue);
    Serial.print(" | Voltage: ");
    Serial.println(voltage, 3);
    if (voltage < 3)
    {
        // Move motor 1 to home position
        digitalWrite(DIR_PIN, HIGH);  // Set direction for Motor 1
        unsigned long home_m1_time = millis();
        run_motor_1(20, home_m1_time);
    }

    delay(50);

    Serial.print("ADC Value1: ");
    Serial.print(adcValue1);
    Serial.print(" | Voltage1: ");
    Serial.println(voltage1, 3);
    if (voltage1 < 3)
    {
        // Move motor 2 to home position
        digitalWrite(DIR_PIN_M2, LOW); // Set direction for Motor 2
        unsigned long home_m2_time = millis();
        run_motor_2(20, home_m2_time);
    }

    if (voltage > 3 && voltage1 > 3) {
        Serial.println("Motors moved to home position");
        return true;
    }
    return false;
    
}


void stepper_loop() {


    Serial.println("Stepper loop started");

    Serial.println("Moving to home position");
    while (!go_to_home_position()) {
        Serial.println("Waiting for motors to reach home position...");
        delay(500);  // Wait before checking again
    }

    Serial.println("Picking the object");
    // Move forward motor 1
    digitalWrite(DIR_PIN, LOW);  // Forward direction for Motor 1
    unsigned long startTime = millis();
    run_motor_1(RUN_TIME_M1, startTime);
    digitalWrite(RELAY_PIN, HIGH);

    delay(2000);  // Pause before changing direction

    digitalWrite(DIR_PIN_M2, HIGH); // Forward direction for Motor 2
    unsigned long pick_time = millis();
    run_motor_2(50, pick_time);

    delay(500);

    // Move forward motor 1
    digitalWrite(DIR_PIN_M2, LOW); // Reverse direction for Motor 2
    unsigned long pick_time_1 = millis();
    run_motor_2(50, pick_time_1);
    delay(500);

    // Move backward motor 1
    digitalWrite(DIR_PIN, HIGH);  // Reverse direction for Motor 1
    unsigned long startTime_2 = millis();
    run_motor_1(RUN_TIME_M1, startTime_2);
    Serial.println("Object Picked");
    delay(1000);
    Serial.println("Placing the object");
    // Move forward motor 2
    digitalWrite(DIR_PIN_M2, HIGH); // Forward direction for Motor 2
    unsigned long startTime_3 = millis();
    run_motor_2(RUN_TIME, startTime_3);

    delay(1000);
    digitalWrite(RELAY_PIN, LOW);
    // Move forward motor 1
    digitalWrite(DIR_PIN_M2, LOW); // Reverse direction for Motor 2
    unsigned long startTime_4 = millis();
    run_motor_2(RUN_TIME, startTime_4);
    Serial.println("Object placed");
    delay(1000);  // Pause before next cycle
}


    


