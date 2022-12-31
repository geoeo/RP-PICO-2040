#include <stdio.h>
#include "pico/stdlib.h"
#include "arducampico.h"
uint8_t header[2] = {0x55,0xAA};
const uint32_t IMSIZE = 96*96;
uint8_t image[IMSIZE] = {0};
struct arducam_config config;

void setup() {
  Serial.begin(115200);
  gpio_init(PIN_LED);
  gpio_set_dir(PIN_LED, GPIO_OUT);
  config.sccb = i2c0;
  config.sccb_mode = I2C_MODE_16_8;
  config.sensor_address = 0x24;
  config.pin_sioc = PIN_CAM_SIOC;
  config.pin_siod = PIN_CAM_SIOD;
  config.pin_resetb = PIN_CAM_RESETB;
  config.pin_xclk = PIN_CAM_XCLK;
  config.pin_vsync = PIN_CAM_VSYNC;
  config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;
  config.pio = pio0;
  config.pio_sm = 0;
  config.dma_channel = 0;
  arducam_init(&config);
}

void loop() {
  gpio_put(PIN_LED, !gpio_get(PIN_LED));
  arducam_capture_frame(&config,image);
  Serial.write(header,2);
  delay(5);
  Serial.write(image,IMSIZE);

}
