#!/bin/bash
stm32flash -w out/stm32-test.hex -v -g 0x0 /dev/ttyUSB0
