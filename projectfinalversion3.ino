#include "HCPCA9685.h"
#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);

const int servo_joint_L_parking_pos = 60;
const int servo_joint_R_parking_pos = 60;
const int servo_joint_1_parking_pos = 70;
const int servo_joint_2_parking_pos = 47;
const int servo_joint_3_parking_pos = 63;
const int servo_joint_4_parking_pos = 63;

int servo_joint_L_pos_increment = 20;
int servo_joint_R_pos_increment = 20;
int servo_joint_1_pos_increment = 20;
int servo_joint_2_pos_increment = 50;
int servo_joint_3_pos_increment = 60;
int servo_joint_4_pos_increment = 40;

int servo_joint_L_parking_pos_i = servo_joint_L_parking_pos;
int servo_joint_R_parking_pos_i = servo_joint_R_parking_pos;
int servo_joint_1_parking_pos_i = servo_joint_1_parking_pos;
int servo_joint_2_parking_pos_i = servo_joint_2_parking_pos;
int servo_joint_3_parking_pos_i = servo_joint_3_parking_pos;
int servo_joint_4_parking_pos_i = servo_joint_4_parking_pos;

int servo_joint_L_min_pos = 10;
int servo_joint_L_max_pos = 180;
int servo_joint_R_min_pos = 10;
int servo_joint_R_max_pos = 180;
int servo_joint_1_min_pos = 10;
int servo_joint_1_max_pos = 400;
int servo_joint_2_min_pos = 10;
int servo_joint_2_max_pos = 380;
int servo_joint_3_min_pos = 10;
int servo_joint_3_max_pos = 380;
int servo_joint_4_min_pos = 10;
int servo_joint_4_max_pos = 120;

int servo_L_pos = 0;
int servo_R_pos = 0;
int servo_joint_1_pos = 0;
int servo_joint_2_pos = 0;
int servo_joint_3_pos = 0;
int servo_joint_4_pos = 0;

char state = 0;

int response_time = 5;
int response_time_4 = 2;
int loop_check = 0;
int response_time_fast = 20;
int action_delay = 600;

const int dirPin = 4;
const int stepPin = 5;
const int stepsPerRevolution = 120;
int stepDelay = 4500;
const int stepsPerRevolutionSmall = 60;
int stepDelaySmall = 9500;

int Pos = 0;

void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(4800);
  delay(3000);
}

void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
    Serial.print(state);
    
    if (state == 'S') {
      baseRotateLeft();
      delay(response_time);
    }
    
    if (state == 'O') {
      baseRotateRight();
      delay(response_time);
    }

    if (state == 'c') {
      shoulderServoForward();
      delay(response_time);
    }
    
    if (state == 'C') {
      shoulderServoBackward();
      delay(response_time);
    }

    if (state == 'p') {
      elbowServoForward();
      delay(response_time);
    }
    
    if (state == 'P') {
      elbowServoBackward();
      delay(response_time);
    }

    if (state == 'U') {
      wristServo1Backward();
      delay(response_time);
    }
    
    if (state == 'G') {
      wristServo1Forward();
      delay(response_time);
    }

    if (state == 'R') {
      wristServoCW();
      delay(response_time);
    }
    
    if (state == 'L') {
      wristServoCCW();
      delay(response_time);
    }

    if (state == 'F') {
      gripperServoBackward();
      delay(response_time);
    }
    
    if (state == 'f') {
      gripperServoForward();
      delay(response_time);
    }
  }
}

void gripperServoForward() {
  if (servo_joint_4_parking_pos_i > servo_joint_4_min_pos) {
    HCPCA9685.Servo(5, servo_joint_4_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_4_parking_pos_i);
    servo_joint_4_parking_pos_i = servo_joint_4_parking_pos_i - servo_joint_4_pos_increment;
  }
}

void gripperServoBackward() {
  if (servo_joint_4_parking_pos_i < servo_joint_4_max_pos) {
    HCPCA9685.Servo(5, servo_joint_4_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_4_parking_pos_i);
    servo_joint_4_parking_pos_i = servo_joint_4_parking_pos_i + servo_joint_4_pos_increment;
  }
}

void wristServoCW() {
  if (servo_joint_3_parking_pos_i > servo_joint_3_min_pos) {
    HCPCA9685.Servo(4, servo_joint_3_parking_pos_i);
    delay(response_time_4);
    Serial.println(servo_joint_3_parking_pos_i);
    servo_joint_3_parking_pos_i = servo_joint_3_parking_pos_i - servo_joint_3_pos_increment;
  }
}

void wristServoCCW() {
  if (servo_joint_3_parking_pos_i < servo_joint_3_max_pos) {
    HCPCA9685.Servo(4, servo_joint_3_parking_pos_i);
    delay(response_time_4);
    Serial.println(servo_joint_3_parking_pos_i);
    servo_joint_3_parking_pos_i = servo_joint_3_parking_pos_i + servo_joint_3_pos_increment;
  }
}

void wristServo1Forward() {
  if (servo_joint_2_parking_pos_i < servo_joint_2_max_pos) {
    HCPCA9685.Servo(3, servo_joint_2_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_2_parking_pos_i);
    servo_joint_2_parking_pos_i = servo_joint_2_parking_pos_i + servo_joint_2_pos_increment;
  }
}

void wristServo1Backward() {
  if (servo_joint_2_parking_pos_i > servo_joint_2_min_pos) {
    HCPCA9685.Servo(3, servo_joint_2_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_2_parking_pos_i);
    servo_joint_2_parking_pos_i = servo_joint_2_parking_pos_i - servo_joint_2_pos_increment;
  }
}

void elbowServoForward() {
  if (servo_joint_L_parking_pos_i < servo_joint_L_max_pos) {
    HCPCA9685.Servo(0, servo_joint_L_parking_pos_i);
    HCPCA9685.Servo(1, (servo_joint_L_max_pos - servo_joint_L_parking_pos_i));
    delay(response_time);
    Serial.println(servo_joint_L_parking_pos_i);
    servo_joint_L_parking_pos_i = servo_joint_L_parking_pos_i + servo_joint_L_pos_increment;
    servo_joint_R_parking_pos_i = servo_joint_L_max_pos - servo_joint_L_parking_pos_i;
  }
}

void elbowServoBackward() {
  if (servo_joint_L_parking_pos_i > servo_joint_L_min_pos) {
    HCPCA9685.Servo(0, servo_joint_L_parking_pos_i);
    HCPCA9685.Servo(1, (servo_joint_L_max_pos - servo_joint_L_parking_pos_i));
    delay(response_time);
    Serial.println(servo_joint_L_parking_pos_i);
    servo_joint_L_parking_pos_i = servo_joint_L_parking_pos_i - servo_joint_L_pos_increment;
    servo_joint_R_parking_pos_i = servo_joint_L_max_pos - servo_joint_L_parking_pos_i;
  }
}

void shoulderServoForward() {
  if (servo_joint_1_parking_pos_i < servo_joint_1_max_pos) {
    HCPCA9685.Servo(2, servo_joint_1_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_1_parking_pos_i);
    servo_joint_1_parking_pos_i = servo_joint_1_parking_pos_i + servo_joint_1_pos_increment;
  }
}

void shoulderServoBackward() {
  if (servo_joint_1_parking_pos_i > servo_joint_1_min_pos) {
    HCPCA9685.Servo(2, servo_joint_1_parking_pos_i);
    delay(response_time);
    Serial.println(servo_joint_1_parking_pos_i);
    servo_joint_1_parking_pos_i = servo_joint_1_parking_pos_i - servo_joint_1_pos_increment;
  }
}

void baseRotateLeft() {
  digitalWrite(dirPin, HIGH);
  for (int x = 0; x < stepsPerRevolution; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  delay(response_time);
}

void baseRotateRight() {
  digitalWrite(dirPin, LOW);
  for (int x = 0; x < stepsPerRevolution; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  delay(response_time);
}

void wakeUp() {
  if (loop_check == 0) {
    for (Pos = 0; Pos < 10; Pos++) {
      HCPCA9685.Servo(1, Pos);
      delay(response_time_fast);
    }
    for (Pos = 400; Pos > 390; Pos--) {
      HCPCA9685.Servo(2, Pos);
      delay(response_time_fast);
    }
    for (Pos = 10; Pos < 20; Pos++) {
      HCPCA9685.Servo(3, Pos);
      delay(response_time);
    }
    for (Pos = 380; Pos > 50; Pos--) {
      HCPCA9685.Servo(4, Pos);
      delay(response_time);
    }
    for (Pos = 50; Pos < 150; Pos++) {
      HCPCA9685.Servo(4, Pos);
      delay(response_time);
    }
    for (Pos = 19; Pos < 100; Pos++) {
      HCPCA9685.Servo(3, Pos);
      delay(response_time);
    }
    loop_check = 0;
  }
}

void flexMotors() {
  if (loop_check == 0) {
    delay(action_delay);
    for (Pos = 100; Pos > 10; Pos--) {
      HCPCA9685.Servo(3, Pos);
      delay(10);
    }
    delay(action_delay);
    for (Pos = 10; Pos < 70; Pos++) {
      HCPCA9685.Servo(3, Pos);
      delay(10);
    }
    delay(action_delay);
    baseRotateLeft();
    delay(action_delay);
    for (Pos = 200; Pos < 380; Pos++) {
      HCPCA9685.Servo(4, Pos);
      delay(10);
    }
    delay(action_delay);
    loop_check = 1;
  }
}