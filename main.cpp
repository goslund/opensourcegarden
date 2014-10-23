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
#include <SerialStream.h>
#include "Arduino/ArduinoFacade.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Server/tcp_server.h"
//#include "Server/udp_server.h"
//#include "Arduino/ArduinosController.h"

void startThread() {
	boost::asio::io_service io_service;
	tcp_server server(io_service);

	io_service.run();	
}

int main() {

	boost::thread t(&startThread);

	std::cout << "Started Thread" << std::endl;

	for (;;) {
		try {
			;
		} catch (...) {
			std::cerr << "Something went wrong..." << std::endl;
		}
	}	
	

	// //udp::socket socket(io_service, udp::endpoint(udp::v4(), 8102));;
	// //socket.open(udp::v4());
	//boost::thread arduino_listener(startThread);

	// boost::array<char, 128> recv_buf;
 //    udp::endpoint sender_endpoint;

	// for (;;) {
		

	// 	size_t len = socket.receive_from(
 //        	boost::asio::buffer(recv_buf), sender_endpoint);

	// 	std::cout.write(recv_buf.data(), len);
	// 	std::cout << std::endl;
	// 	std::cout.flush();
	// }

	// tcp_server* acceptor = new tcp_server(io_service);
	// for(;;) {
		
	// 	// tcp::socket socket(io_service);
 //  //     	acceptor.accept(socket);
	// }


	//ArduinosController* controller = ArduinosController::getInstance();

	// try
 //  		{
	// 	boost::asio::io_service io_service;
	// 	tcp_server server(io_service);
	// 	io_service.run();
	// }	catch (std::exception& e)
 //  	{
 //   		std::cerr << e.what() << std::endl;
 //  	}

	// int i = 1;
	// while(i <= 100) {
	// 	arduino->sendMessage("digitalWrite:13:0");
	// 	sleep(1);
	// 	arduino->sendMessage("digitalWrite:13:1");
	// 	sleep(1);
	// 	i++;
	// }
	//serialStream();

	//int fd = openfile(port);
	// std::cout << device["name"].as<std::string>() << "\n";
	
	// YAML::Node port = config["port"];

	// std::cout << port.as<std::string>() << "\n";
	return 0;

}

