#include <XBee.h>

// Create an XBee object at the top of your sketch
XBee xbee = XBee();

// Start the serial port
Serial.begin(9600);
// Tell XBee to use Hardware Serial. It's also possible to use SoftwareSerial
xbee.setSerial(Serial);

// Create an array for holding the data you want to send.
uint8_t payload[] = { 'H', 'i' };

// Specify the address of the remote XBee (this is the SH + SL)
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x403e0f30);

// Create a TX Request
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

// Send your request
xbee.send(zbTx);
