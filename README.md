# ESP32-servo-motor-control
ESP32 Arduino MCPWM servo motor SG90 perfect control

> the traditional ESP32 PWM code would be like this:
```javascript
  pinMode(SERVO_PIN, OUTPUT);
  ledcSetup(0, 50, 10); //20mS
  ledcAttachPin(SERVO_PIN, 0);
  ledcWrite(0, 76);
```

> however, using this way to stop the PWM outpt, there is a unfinished pulse at the end of the waveform sometimes, it might cause a unwanted vibration for servo motor control.

![waveform with bug](/before.jpg)

> using MCPWM module to start PWM and stop PWM will generate a perfect finished wavefrom. Here we access the MCPWM registers directly to do this.

![waveform perfect](/after.jpg)
