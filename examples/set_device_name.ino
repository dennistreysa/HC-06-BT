#include "bluetooth.h"

Bluetooth BT(2, 3);

void setup () {
      Serial.begin(9600);
      
      BT.Begin();
      BT.Reset();
      BT.setDeviceName("HC-06-BT");
      BT.setDevicePin("5464");
      
}

void loop () {
	char buffer[100];

	BT.getDeviceName(buffer);

	Serial.println(buffer);

	delay(5000);

	BT.getVersion(buffer);

	Serial.println(buffer);

	delay(5000);
}
