#!/bin/bash
make -f makeEspArduino.mk \
  ESP_ROOT=~/dev/esp8266 \
  BOARD=nodemcuv2 flash
