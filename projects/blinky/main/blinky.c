#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <esp8266/gpio_register.h>
#include "esp_system.h"

#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/hw_timer.h"


#define TAG "BLINKY"
#define GPIO_LED GPIO_NUM_2


//UBaseType_t timer_callback_count = 0;
//bool led_value = pdFALSE;


void toggle_led(void *arg)
{
    static bool led_value = pdFALSE;

    gpio_set_level(GPIO_LED, led_value);    
    led_value = !led_value;
}

void init_gpio()
{
    ESP_LOGI(TAG, "Configuring GPIO...");
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ull << GPIO_LED);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void app_main()
{
    init_gpio();

    hw_timer_init(toggle_led, NULL);
    hw_timer_alarm_us(1000000, true /* reload */);

    for (;;);

    hw_timer_deinit();
}