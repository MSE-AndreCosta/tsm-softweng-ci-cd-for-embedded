target remote :3333
monitor reset
monitor semihosting enable
monitor semihosting ioclient 2
load
tbreak main
continue
