#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"


volatile uint8_t commandStatusAsync = 0;
volatile uint32_t servoDutySet = 0;

void servoResetOperator() {
  MCPWM1.channel[2].generator[0].utez = 1;
  MCPWM1.channel[2].generator[0].utea = 1;
  MCPWM1.channel[2].generator[0].uteb = 1;
  MCPWM1.channel[2].generator[0].utep = 1;

}
void servoStartOperator(uint32_t duty) {

  //MCPWM1.timer[1].period.period = freq * 400;

  MCPWM1.channel[2].cmpr_value[0].cmpr_val = duty * 20;
  MCPWM1.channel[2].generator[0].utez = 2;
  MCPWM1.channel[2].generator[0].utea = 1;
  MCPWM1.channel[2].generator[0].uteb = 0;
  MCPWM1.channel[2].generator[0].utep = 0;

}
void servoConfig() {
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM2A, SERVO_PIN);

  MCPWM1.clk_cfg.prescale = 15;
  MCPWM1.timer[2].period.prescale = 9;
  MCPWM1.timer[2].period.period = 50 * 400;//
  MCPWM1.timer[2].period.upmethod = 0;//immediate
  MCPWM1.timer_sel.operator2_sel = 2;
  MCPWM1.channel[2].cmpr_value[0].cmpr_val = 50 * 200;
  //MCPWM1.channel[2].cmpr_value[1].cmpr_val = 50 * 200;
  servoResetOperator();
  MCPWM1.timer[2].mode.start = 2;//free run
  MCPWM1.timer[2].mode.mode = 1;//increase


}
static void servoTask(void *arg) {

  servoStartOperator(servoDutySet);
  _delay_ms(200);
  servoResetOperator();

  commandStatusAsync = 2;
  //SERIAL_DEBUG("[servo] finished\n");
  vTaskDelete(NULL);
}

void servoRun(float duty) {
  servoDutySet = int(duty * 10.0);
  xTaskCreate(servoTask, "servoTask", 4096, NULL, 5, NULL);
}
