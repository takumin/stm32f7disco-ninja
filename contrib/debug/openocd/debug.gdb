set tui border-kind ascii

target remote localhost:3333

monitor reset halt
load
monitor reset init

thbreak prvIdleTask

continue
