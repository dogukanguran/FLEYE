void setup() {

Serial.begin(9600);
delay(1000);
Serial.flush();                                                            // Clear serial buffer

// ------ Xbee module configuration -------------

command_mode();
reset();
read_parameter();
config_parameter();
read_parameter();

// ------ End Xbee module configuration ---------

Serial.println(" \r\n ------ Receiving data from GPS -------- ");
}

void loop() {

read_data();                                                         // Reads data sended throw Xbee and writes to the serial port

}

// XBEE control commands : These functions manage the commands to enter and out from configuration mode,reset and save data
//---------------------------------------------------------------------------------------------------------
void command_mode(){                                                        // Enter in configuration mode
while(Serial.available()==0){
delay(1000);
Serial.print("+++");
delay(1000);
}
read_data();
}

void exit_cn(){                                                             // Exit command mode
Serial.println("\r\nATCN");
read_data();
Serial.println("\r\n***** Exit command mode *****");
delay(1000);
}

void reset(){                                                              // Reset Xbee (If you have not use write_config this functions reset the device to his previous values)
Serial.println("\r\nATRE");
read_data();
Serial.println("\r\n***** Device reset *****");
delay(1000);
}

void write_config(){                                                     // Writes the configuration in the Xbee module
Serial.println("\r\nATWR");
read_data();
Serial.println("\r\n***** Writting configuration in Xbee module *****");
delay(1000);
}

//-------------------------------------------------------------------------------------------------------------

// XBEE visualization commands : These functions read and write data from or to xbee or serial buffer
//-------------------------------------------------------------------------------------------------------------
void read_data(){               // Reading data response from serial xbee
byte data;
while(Serial.available()==0){}
while(Serial.available()>0){
data=Serial.read();
delay(10);                  // Waiting to receive new data
write_data(data);
}
Serial.flush();             // Clear serial buffer
}

void write_data(byte data){     // Write data from xbee to serial
Serial.print(char(data));
}

void read_parameter(){        // Reading configuration parameter
Serial.println("\r\n-------- Reading device parameter --------");

Serial.println("\r\nATID");  // Network ID
read_data();

Serial.println("\r\nATCH");  // Channel ID
read_data();

Serial.println("\r\nATMY");  // Address of the module
read_data();

Serial.println("\r\nATSH");  // Serial number of XBee  high (32 bits)
read_data();

Serial.println("\r\nATSL"); // Serial number of XBee low (32 bits)
read_data();

Serial.println("\r\nATDH"); // Destination address high (32 bits)
read_data();

Serial.println("\r\nATDL"); // Destination address low (32 bits)
read_data();

Serial.println("\r\nATBD"); // Baud rate
read_data();
}

void config_parameter(){        // Reading configuration parameter
Serial.println("\r\n-------- Config device parameter --------");

Serial.println("\r\nATID3329"); // Network ID
read_data();

Serial.println("\r\nATCHD");    // Channel ID
read_data();

//Serial.println("\r\nATDH");    // Destination address high (32 bits)
//read_data();

//Serial.println("\r\nATDL");    // Destination address low (32 bits)
//read_data();

}
