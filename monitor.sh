#!/bin/bash

case $1 in
  start) 
    screen -c .screenrc -S ino_monitor /dev/ttyUSB0 115200;;
  stop) 
    screen -X -S ino_monitor quit;;
esac

