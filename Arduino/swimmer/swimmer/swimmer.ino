  // including software Serial port
  // arduino uno has only one serial port and this could be another sensor(gyro)
  // so, we are using ports no:9 and no:8 to communicate
  #include <SoftwareSerial.h>
  
  // Constants
  #define rxPin 9      //rx pin in gps connection
  #define txPin 8      //tx pin in gps connection
  
  // set up the serial port
  SoftwareSerial gps = SoftwareSerial(rxPin, txPin);
  
  // variables
  byte byteGPS = 0;
  int i = 0;
  int h = 0;
  
  // Buffers for data input
  char inBuffer[300] = "";
  char GPS_RMC[100]="";
  char GPS_GGA[100]="";
  
  void setup() {
  // Arduino serial port configuration
  Serial.begin(9600);
  delay(1000);// giving time to arduino to wait the connection
  Serial.flush();
  
  // Xbee module configuration
  command_mode();
  reset();
  read_parameter();
  config_parameter();
  read_parameter();
  
  // Gps serial port configuration
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  gps.begin(4800);
  }
  
  void loop() {
  while(!gps.available()){};  
  // Gps data parser 
  
  // Read the RMC sentence from GPS
  // RMC Format : $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a,m,*hh<CR><LF>
  /*
  Field Number:
  1. UTC Time
  2. Status, V=Navigation receiver warning A=Valid
  3. Latitude
  4. N or S
  5. Longitude
  6. E or W
  7. Speed over ground, knots
  8. Track made good, degrees true
  9. Date, ddmmyy
  10. Magnetic Variation, degrees
  11. E or W
  12. FAA mode indicator (NMEA 2.3 and later)
  13. Checksum
  */
  byteGPS = 0;
  byteGPS = gps.read();
  while(byteGPS != 'R'){
    byteGPS = gps.read();
  }
  GPS_RMC[0]='$';
  GPS_RMC[1]='G';
  GPS_RMC[2]='P';
  GPS_RMC[3]='R';
  
  i = 4;
  while(byteGPS != '*'){
    byteGPS = gps.read();
    inBuffer[i]=byteGPS;
    GPS_RMC[i]=byteGPS;
    i++;
  }
  
  // Read GGA sentence from GPS
  // GGA Format : $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<CR><LF>
  /*
  Field Number: 
  1. Universal Time Coordinated (UTC)
  2. Latitude
  3. N or S (North or South)
  4. Longitude
  5. E or W (East or West)
  6. GPS Quality Indicator,
       - 0 - fix not available,
       - 1 - GPS fix,
       - 2 - Differential GPS fix
             (values above 2 are 2.3 features)
       - 3 = PPS fix
       - 4 = Real Time Kinematic
       - 5 = Float RTK
       - 6 = estimated (dead reckoning)
       - 7 = Manual input mode
       - 8 = Simulation mode
  7. Number of satellites in view, 00 - 12
  8. Horizontal Dilution of precision (meters)
  9. Antenna Altitude above/below mean-sea-level (geoid) (in meters)
  10. Units of antenna altitude, meters
  11. Geoidal separation, the difference between the WGS-84 earth
       ellipsoid and mean-sea-level (geoid), "-" means mean-sea-level
       below ellipsoid
  12. Units of geoidal separation, meters
  13. Age of differential GPS data, time in seconds since last SC104
       type 1 or 9 update, null field when DGPS is not used
  14. Differential reference station ID, 0000-1023
  15. Checksum
  */
  byteGPS = 0;
  byteGPS = gps.read();
  while(byteGPS != 'A'){
  byteGPS = gps.read();
  }
  GPS_GGA[0]='$';
  GPS_GGA[1]='G';
  GPS_GGA[2]='P';
  GPS_GGA[3]='G';
  GPS_GGA[4]='G';
  GPS_GGA[5]='A';
  
  i = 6;
  while(byteGPS != '*'){
    byteGPS = gps.read();
    inBuffer[i]=byteGPS;
    GPS_GGA[i]=byteGPS;
    i++;
  }
  
  // print the GGA sentence to USB(xBee)
  Serial.print("GGA sentence: ");
  h = 0;
  while(GPS_GGA[h] != 42){
    Serial.write(GPS_GGA[h]);
    h++;
  }
  
  // print the RMC sentence to USB(xBee)
  Serial.print("RMC sentence: ");
  h = 0;
  while(GPS_RMC[h] != 42){
    Serial.write(GPS_RMC[h]);
    h++;
  }
  delay(1000);
  }
  
  //---------------------------------------------------------------------------------------------------------
  
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
  
  void reset(){                                                              // Reset Xbee
    Serial.println("\r\nATRE");
    read_data();
    Serial.println("\r\n***** Device reset *****");
    delay(1000);
  }
  
  void write_config(){                                                     // Writes the configuration in the xbee
    Serial.println("\r\nATWR");
    read_data();
    Serial.println("\r\n***** Writting configuration in Xbee module *****");
    delay(1000);
  }
  
  //-------------------------------------------------------------------------------------------------------------
  
  // XBEE visualization commands : These functions read and write data from or to xbee or serial buffer
  //-------------------------------------------------------------------------------------------------------------
  void read_data(){                 // Reading data response from serial xbee
    byte data;
    while(Serial.available()==0){}
    while(Serial.available()>0){
      data=Serial.read();
      delay(10);                  // Waiting to receive new data
      write_data(data);
    }
    Serial.flush();                    // Clear serial buffer
  }
  
  void write_data(byte data){    // Write data from xbee to serial
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
    
    Serial.println("\r\nATDH");    // Destination address high (32 bits)
    read_data();
    
    Serial.println("\r\nATDL");    // Destination address low (32 bits)
    read_data();
  
  }
