# HC-06-BT
An Arduino library for the HC-06 Bluetooth module using the BC417 chip. Made for version "hc01.comV2.0", but might work with others.

## Background
I was unable to get my Bluetooth module going, so I combined some other libraries to code my own. Maybe this might be helpful for others.

## Config
There is not much you can configure. A minimal setup looks like the following:

```c++
Bluetooth BT(2, 3); // RX, TX
```

If you want to, you can specify the baudrate of the controller:

```c++
Bluetooth BT(2, 3, 9600); // RX, TX
```

## Limitations
As you can read [here](https://www.arduino.cc/en/Reference/SoftwareSerial) there are some limitations to the SoftwareSerial:

* If using multiple software serial ports, only one can receive data at a time.
* Not all pins on the Mega and Mega 2560 support change interrupts, so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).
* Not all pins on the Leonardo and Micro support change interrupts, so only the following can be used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
* On Arduino or Genuino 101 the current maximum RX speed is 57600bps
* On Arduino or Genuino 101 RX doesn't work on Pin 13

## Resources

* [Martyn Currey's Blog](http://www.martyncurrey.com/hc-06-hc01-comv2-0/)
* [Chinese original datasheet](http://www.hc01.com/Public/uploads/file/HC-05AT.pdf)

## Other Libraries

* [Android with Arduino - Bluetooth](https://github.com/aron-bordin/Android-with-Arduino-Bluetooth) by aron-bordin
* [PNG-Arduino-Framework-master](https://github.com/aron-bordin/PNG-Arduino-Framework) by aron-bordin
