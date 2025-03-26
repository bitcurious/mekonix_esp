#include <Arduino.h>
#include "ros_communication.h"

#include "stepper_control.h"


RosCommunication ros_communication ;


void setup() {
    // motor_setup();
    steper_motor_setup();
    ros_communication.initialize();
    ros_communication.subscriber_define();
    ros_communication.executors_start();
}

void loop() {
    ros_communication.start_receiving_msgs();

}
