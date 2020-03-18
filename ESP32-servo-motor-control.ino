/*
   define GPIO PIN for stepper motor A and stepper motor B
*/
#define SERVO_PIN 17

#define _delay_ms(ms) vTaskDelay((ms) / portTICK_RATE_MS)
#define DEBUG_ESP_ON 1 // comment this line to disable serial log
#ifdef DEBUG_ESP_ON
#define SERIAL_DEBUG(...) Serial.printf( __VA_ARGS__ )

#else
#define SERIAL_DEBUG(...)
#endif
#include "SERVO.CPP"

#define SERVO_ANGLE_135  10.0
#define SERVO_ANGLE_45  5.0
#define SERVO_ANGLE_90  7.5
void setup() {
  Serial.begin(115200);
  SERIAL_DEBUG("Serial begin\n");
  
  //use MCPWM module to generate PWM
  servoConfig();

  servoRun(SERVO_ANGLE_90);
  
  //traditional way to generate PWM
  /*
  pinMode(SERVO_PIN, OUTPUT);
  ledcSetup(0, 50, 10);
  ledcAttachPin(SERVO_PIN, 0);
  ledcWrite(0, 76);

  _delay_ms(200);
  ledcWrite(0, 0);
  ledcDetachPin(SERVO_PIN);
  */
}

void loop() {
  // put your main code here, to run repeatedly:

}
