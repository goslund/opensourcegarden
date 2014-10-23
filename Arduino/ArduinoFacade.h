/* 
 * File:   OSGAlNode.h
 * Author: Geoff Oslund
 *
 * Created on February 14, 2013, 3:16 PM
 */

#ifndef OSGARDUINOFACADE_H
#define	OSGARDUINOFACADE_H
#include <iostream>
#include <string>
#include <SerialStream.h>
using namespace std;
using namespace LibSerial;

class ArduinoFacade {
public:
	ArduinoFacade(string file_descriptor) {
		arduino.Open("/dev/ttyACM1");
		arduino.SetBaudRate(SerialStreamBuf::BAUD_9600);  
	    arduino.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	    arduino.SetParity( SerialStreamBuf::PARITY_NONE );
	    arduino.SetNumOfStopBits(1);
	}

	~ArduinoFacade() {
		arduino.Close();
	}

	string getMessage() {
		string buffer;
		while( arduino.rdbuf()->in_avail() > 0 )
	    {
	        char next_byte;
	        arduino.get(next_byte);
	        buffer = buffer + next_byte;
	    }
	    return buffer;
	}

	string sendMessage(string message) {
		arduino << message << endl;
		usleep(100000);
		return getMessage();

	}
private:
	SerialStream arduino;
};

#endif /* OSGARDUINOFACADE_H */