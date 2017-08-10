/*
 *  This is an Arduino class written for the HC-06 Bluetooth module
 *  It uses the SoftwareSerial library
 *
 *  Author: dennistreysa
 *
 *  Last Changed: 2017-02-04
 */

#include "bluetooth.h"


/*
 *  Constructor of Bluetooth class
 *
 *  @param
 *      RX          : Number of the pin that shall be used as RX
 *      TX          : Number of the pin that shall be used as TX
 *      _baudrate   : The baudrate the controller should use
 */
Bluetooth::Bluetooth (unsigned int RX, unsigned int TX, unsigned int baudrate) {

    this->_RXPin = RX;
    this->_TXPin = TX;
    this->_baudrate = baudrate;

    this->_btSerialDevice = new SoftwareSerial(RX, TX);

    // Init strings
    memset(this->_messageBuffer, 0, sizeof(this->_messageBuffer));
    memset(this->_deviceName, 0, sizeof(this->_deviceName));
    memset(this->_devicePin, 0, sizeof(this->_devicePin));
}


/*
 */
Bluetooth::~Bluetooth () {
    delete this->_btSerialDevice;
}


/*
 *  Initializes the bluetooth controller
 */
void Bluetooth::Begin () {
    this->_btSerialDevice->begin(this->_baudrate);
    delay(BT_DEV_WRITE_WAIT);

    this->_btSerialDevice->write("AT");
    delay(BT_DEV_WRITE_WAIT);

    this->_initialized = true;

    this->setBaudrate(this->_baudrate);

    this->_clearSerial();
}


/*
 *  Resets the bluetooth controller
 */
void Bluetooth::Reset () {
    if (this->_initialized) {
        strcpy(this->_messageBuffer, "AT+RESET");
        this->_write();
    }
}


/*
 *  Read serial data from the device (if present).
 *
 *  @param
 *      buffer      : A buffer to store the read seria data
 *      bufferSize  : The maximum number of bytes the buffer can hold
 *
 *  @return
 *      The real number of bytes that were read from the serial
 */
int Bluetooth::Read (char buffer[], int bufferSize) {
    
    int bytesRead = 0;

    if (bufferSize > 0) {
        while (this->_btSerialDevice->available() && bytesRead < bufferSize) {
            buffer[bytesRead] = this->_btSerialDevice->read();
            bytesRead++;
        }
    }

    return bytesRead;
}


void Bluetooth::Write (char buffer[]) {
    this->_btSerialDevice->write(buffer);
}

void Bluetooth::_clearSerial () {

    volatile char trash; 

    while (this->_btSerialDevice->available()) {
        trash = this->_btSerialDevice->read();
    }
}


/*
 *  Internal function to write the buffer to the serial and wait some while
 */
void Bluetooth::_write () {
    this->Write(this->_messageBuffer);
    delay(BT_DEV_WRITE_WAIT);
}


/*
 *  Internal function to write the buffer to the serial and write back answer
 *  to a buffer
 *
 *  @param
 *      buffer : A buffer to write the answer to
 */
void Bluetooth::_writeReceive (char buffer[]) {
    int index = 0;

    this->_clearSerial();

    this->_write();

    while (this->_btSerialDevice->available()) {
        buffer[index] = this->_btSerialDevice->read();
        index++;
    }

    buffer[index] = '\0';
}


/*
 *  Sets the device baudrate
 *
 *  @param
 *      baudrate :  The new baudrate of the device
 */
void Bluetooth::setBaudrate (unsigned int baudrate) {

    /*
        1---1200
        2---2400
        3---4800
        4---9600    --> default
        5---19200
        6---38400
        7---57600
        8---115200
        9---230400
        A---460800
        B---921600
        C---1382400
    */
    if (this->_initialized) {

        this->_baudrate = baudrate;

        strcpy(this->_messageBuffer, "AT+BAUD");

        switch (baudrate) {
            case 1200 : {
                strcat(this->_messageBuffer, "1");
                break;
            }
            case 2400 : {
                strcat(this->_messageBuffer, "2");
                break;
            }
            case 4800 : {
                strcat(this->_messageBuffer, "3");
                break;
            }
            case 9600 : {
                strcat(this->_messageBuffer, "4");
                break;
            }
            case 19200 : {
                strcat(this->_messageBuffer, "5");
                break;
            }
            case 38400 : {
                strcat(this->_messageBuffer, "6");
                break;
            }
            case 57600 : {
                strcat(this->_messageBuffer, "7");
                break;
            }
            case 115200 : {
                strcat(this->_messageBuffer, "8");
                break;
            }
            case 230400 : {
                strcat(this->_messageBuffer, "9");
                break;
            }
            case 460800 : {
                strcat(this->_messageBuffer, "10");
                break;
            }
            case 921600 : {
                strcat(this->_messageBuffer, "11");
                break;
            }
            case 1382400 : {
                strcat(this->_messageBuffer, "12");
                break;
            }
            default : {
                // Fallback to default
                this->_baudrate = BT_DEV_DEFAULT_BAUDRATE;
                strcat(this->_messageBuffer, "4");
                break;
            }
        }

        this->_write();
    }
}


/*
 *  Sets the name of the device
 *
 *  @param
 *      name :  The new name of the device
 */
void Bluetooth::setDeviceName (const char name[]) {

    if (strlen(name) <= BT_DEV_MAX_DEV_NAME) {
        strcpy(this->_messageBuffer, "AT+NAME");
        strcat(this->_messageBuffer, name);

        strcpy(this->_deviceName, name);
        
        this->_write();
    }
}


/*
 *  Sets the pin of the device
 *
 *  @param
 *      pin: The new pin of the device
 */
void Bluetooth::setDevicePin (const char pin[]) {
    if (strlen(pin) == 4) {
        for (int c = 0; c < 4; c++) {
            if (pin[c] < 0x30 || pin[c] > 0x90) {
                return;
            }
        }

        strcpy(this->_messageBuffer, "AT+PIN");
        strcat(this->_messageBuffer, pin);

        strcpy(this->_devicePin, pin);
        
        this->_write();
    }
}


/*
 *  Get the RX pin the device is using
 *
 *  @return
 *      The number of the RX pin
 */
unsigned int Bluetooth::getRXPin () {
    return this->_RXPin;
}


/*
 *  Get the TX pin the device is using
 *
 *  @return
 *      The number of the TX pin
 */
unsigned int Bluetooth::getTXPin () {
    return this->_RXPin;
}


/*
 *  Get the name of the device
 *  Note: This does NOT query the module!
 *
 *  @return
 *      The name of the device
 */
void Bluetooth::getDeviceName (char buffer[]) {
    strcpy(buffer, this->_deviceName);
}


/*
 *  Get the version string of the device
 *  Note: This DOES query the module!
 *
 *  @return
 *      The version string of the device
 */
void Bluetooth::getVersion (char buffer[]) {
    strcpy(this->_messageBuffer, "AT+VERSION");
    this->_writeReceive(buffer);
}


/*
 *  Get the pin of the device
 *  Note: This does NOT query the module!
 *
 *  @return
 *      The pin of the device
 */
void Bluetooth::getDevicePin (char buffer[]) {
    strcpy(buffer, this->_devicePin);
}
