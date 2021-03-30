#include <Servo.h>
Servo ESC;     // create servo object to control the ESC
int pwmSpeed;  // value from the analog pin
int convertedSpeed; 

#define ESC_MIN_THROTTLE            1070
#define ESC_MAX_THROTTLE            1852
#define ESC_MID_THROTTLE            1480
#define ESC_REVERSE_THROTTLE        1488

#define ESC_ARM_SIGNAL              1480
#define ESC_ARM_TIME                2000

unsigned long start_of_motor_arm_first = 0;
unsigned long start_of_motor_arm_second = 0;
unsigned long time_for_motor_arm = 4000;
long state = 0;
void setup() {
  Serial.begin(9600);
  // Attach the ESC on pin 9
  ESC.attach(A0,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 


  delay(1000);
  start_of_motor_arm_first = millis();
  state = 1;


}
void loop() {
    if (start_of_motor_arm_first + time_for_motor_arm > millis()) {
      state = 2;
      pwmSpeed = ESC_ARM_SIGNAL; // reads the value of the potentiometer (value between 0 and 1023)
    } else if (start_of_motor_arm_first + (time_for_motor_arm * 2) > millis()) {
      state = 3;
      pwmSpeed = 1500; // reads the value of the potentiometer (value between 0 and 1023)
    } else {
      state = 4;
      pwmSpeed = 1500;
    }
    convertedSpeed = pwmSpeed;//map(pwmSpeed, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
    ESC.writeMicroseconds(convertedSpeed);//();    // Send the signal to the ESC
    Serial.println(state);
    delay(10);
}
