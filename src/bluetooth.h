/*
 *	This is an Arduino class written for the HC-06 Bluetooth module
 *	It uses the SoftwareSerial library
 *
 *	Author: dennistreysa
 *
 *	Last Changed: 2017-02-04
 */

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

// Constants
#define BT_DEV_MAX_DEV_NAME 	40
#define BT_DEV_LONGEST_OPCODE	10 // AT+VERSION
#define BT_DEV_DEFAULT_BAUDRATE	9600
#define BT_DEV_WRITE_WAIT		1200

// Includes
#include "Arduino.h"
#include <SoftwareSerial.h>

class Bluetooth {
	private:
		SoftwareSerial	*_btSerialDevice;
		bool			_initialized = false;
		unsigned int	_RXPin;
		unsigned int	_TXPin;
		unsigned int	_baudrate;
		char			_messageBuffer[BT_DEV_LONGEST_OPCODE + BT_DEV_MAX_DEV_NAME + 1];
		char			_deviceName[BT_DEV_MAX_DEV_NAME + 1];
		char			_devicePin[4 + 1];

		void _clearSerial();
		void _write();
		void _writeReceive (char buffer[]);


	public:
		Bluetooth (unsigned int RX = 2, unsigned int TX = 3, unsigned int baudrate = BT_DEV_DEFAULT_BAUDRATE);
		~Bluetooth ();
		void Begin ();
		void Reset ();
		int Read (char buffer[], int bufferSize);
		void Write (char buffer[]);
		void setBaudrate (unsigned int baudrate);
		void setDeviceName (const char name[]);
		void setDevicePin (const char pin[]);
		unsigned int getRXPin ();
		unsigned int getTXPin ();
		void getVersion (char buffer[]);
		void getDeviceName (char buffer[]);
		void getDevicePin (char buffer[]);
};

#endif