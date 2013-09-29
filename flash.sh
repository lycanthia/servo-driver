#!/bin/bash
stm32flash -w out/servo-driver.hex -v -g 0x0 /dev/ttyUSB0
