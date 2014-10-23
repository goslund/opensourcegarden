/*
 * Main.cpp
 *
 *  Created on: 9-Jan-2009
 *      Author: root
 */


/////////////////////////////////////////////////
// Serial port interface program               //
/////////////////////////////////////////////////

#include <stdio.h> // standard input / output functions
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <boost/tokenizer.hpp>
// #include <SerialStream.h>
// #include "Arduino/ArduinoFacade.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Server/tcp_server.h"
#include "Server/WebClientServer.h"

//#include "Server/udp_server.h"
//#include "Arduino/ArduinosController.h"

void startArduinoThread() {
	boost::asio::io_service io_service;
	tcp_server server(io_service);

	io_service.run();	
}

void startWebclientThread() {
	boost::asio::io_service io_service;
	WebClientServer server(io_service);
	io_service.run();
}

int main() {

	boost::thread t(&startArduinoThread);
	boost::thread t2(&startWebclientThread);
	std::cout << "Started Thread" << std::endl;



	for (;;) {
		try {
			;
		} catch (...) {
			std::cerr << "Something went wrong..." << std::endl;
		}
	}	

	return 0;

}

