
#include "tcp_connection.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <string>

#ifndef ARDUINOCONNECTOR_H
#define	ARDUINOCONNECTOR_H

#define STATE_DISCONNECTED 0
#define STATE_CONNECTED 1
#define STATE_CHECK_RECEIVE 2
#define STATE_CHECK_SEND 3 
#define STATE_PARSE_MESSAGE 4
#define STATE_PING 5

#define SEND_SYN 0
#define RECEIVE_ACK 1
#define DISCONNECT 2
#define DISCONNECT_FINISHED 3
#define CONNECTED 4


class tcp_connection;

using namespace boost;
using namespace boost::posix_time;
class ArduinoConnector {
private:
	tcp_connection::pointer connection;
	int state;
	bool ack;
	bool syn;
	std::string current_cmd;
	std::string command;
	std::string command_buf;
	tokenizer<char_separator<char> >::iterator it;
	boost::posix_time::ptime last_ping;
	boost::posix_time::ptime loop_start;

public:
	ArduinoConnector(tcp_connection::pointer c_in) {
		this->connection = c_in;
		state = STATE_CONNECTED, ack =0, syn=0;
		last_ping = ptime(microsec_clock::local_time());
		current_cmd = "";
	}

	void loop() {
		for(;;) {
			// std::cout << "state: " << state << std::endl;	
			loop_start = ptime(microsec_clock::local_time());
			// time_duration td(loop_start - last_ping);
			time_duration td = loop_start - last_ping;
			long time_since_last_ping = td.total_milliseconds();


			//std::cout << "msec: " << msec << std::endl;	
			// std::cout << "Loop start: " << boost::posix_time::to_simple_string(loop_start) << 
				// std::endl << "Last ping: " <<boost::posix_time::to_simple_string(last_ping);
			switch(state) {
				case STATE_CONNECTED: {
					if (time_since_last_ping > 10000) {
						state = STATE_PING;
					} else if (syn == 0) {
						connection->sendMessage("OSG/1.0:SYN;\n\0");
						syn = 1;
					} else {
						tcp::socket& socket_ = connection->socket();
						

						if(socket_.available() > 0) {
							std::cout << "socket available: " << socket_.available() << std::endl;
							command = connection->receive_command();

							command_buf.append(command);

							int len = command_buf.length();


							
								



								

							if ( (len > 0) && command_buf.compare(len-1, 1,";") == 0) {
								command_buf[len-1] = 0;
								std::cout << "command buffer done" << std::endl;
								current_cmd = string(command_buf);

								 std::cout << "current command: " << current_cmd << std::endl;

								
									std::cout << "Input Received: " << command_buf << std::endl;		
									state = STATE_CHECK_RECEIVE;
								
									command_buf = "";
									std::cout << "Input Received: " << command_buf << std::endl;
									std::cout << "current command: " << current_cmd << std::endl;
							} 

					
							

							// command = "OSG/!.0:SYN\n\0";
							command = string("");
							std::cout << "after receive_command: " << current_cmd << std::endl;
							
						}
						
					}
				}
				break;

				case STATE_CHECK_RECEIVE: {
					// std::cout << "CHeck receive!!" << std::endl;
					// generate templated separator for the iterator ":"
					char_separator<char> sep(":");

					// tokenize the string
					tokenizer<char_separator<char> > tokens(current_cmd, sep);

					//get the first one
					it = tokens.begin();
					
					const char* header = ((string) *it).c_str();
					
					// std::cout << "header: " << header << std::endl;
					
					//if the header matches the protocol...
					if (strcmp(header, "OSG/1.0") == 0) {
						//print it
						std::cout << "header: " << header << std::endl;

						//do whatever
						state = STATE_PARSE_MESSAGE;
						break;
					}  // else just go to next message
					
					//clear "command buffer" for next run		
					current_cmd = string("");
					state = STATE_CONNECTED;
					
				}

				break;


				case STATE_PARSE_MESSAGE: {
					//update the iterator
					it++;

					std::cout << "state parse message: \"" <<  *it << "\"" << std::endl;
					// std::cout << "Compare: " << ((string) "ACK").compare(*it) << std::endl;
					std::cout << "Compare: " << (((string) "ACK") == (*it)) << std::endl;

					 if( (((string) "ACK") == (*it)) == 0) {
						//acknowledged, get a status report (turn on led for now)
						//std::cout << *it << std::endl;
						connection->sendMessage("OSG/1.0:COMMAND:NEOPIXEL:1:ON:255:255:255\n\0");
						connection->sendMessage("OSG/1.0:COMMAND:NEOPIXEL:1:ON:255:128:128\n\0");
					}

					current_cmd = string("");
					state = STATE_CONNECTED;
				}
				break;

				case STATE_PING: {
					last_ping = ptime(microsec_clock::local_time());
					connection->sendMessage("OSG/1.0:PING\n\0");
					std::cout << "PING" << std::endl;
					state = STATE_CONNECTED;
				}
				break;

			}
		}	
	}

// // 		while(state != DISCONNECT_FINISHED ) {
// // 			std::cout << "State: " << state << std::endl;
// // 			switch(state) {
// // 				case SEND_SYN: {
// // 					connection->sendMessage("OSG/1.0:SYN\n\0");

// // 					state = RECEIVE_ACK;
// // 				}
// // 				break;

// // 				case RECEIVE_ACK: {
					 
// // 					try{ 
						
// // 						std::string command = connection->receive_command();
// // 						std::cout << "Input Received: " << command << std::endl;
						
// // 						//generate templated separator for the iterator ":"
// // 						char_separator<char> sep(":");

// // 						//tokenize the string
// // 						tokenizer<char_separator<char> > tokens(command, sep);

// // 						//get the first one
// // 						tokenizer<char_separator<char> >::iterator it = tokens.begin();
						
// // 						const char* header = ((string) *it).c_str();
// // 						//print it
						
// // 						if (strcmp(header, "OSG/1.0") == 0) {
// // 							std::cout << "header: " << header << std::endl;
// // 						} else {
// // 							//ignore it

// // 						}
// // //						std::cout << command.compare("exit") << endl;
// // 						std::cout << state << std::endl;
// // 						state = CONNECTED;
// // 						break;
// // 					} catch(std::exception& e) {
// // 						std::cout << "disconnected" << std::endl;
// // 						state = DISCONNECT;
// // 					}
// // 				}		
// // 				break;

// // 				case DISCONNECT: {
// // 					std::cout << "disconnecting" << std::endl;
// // 					connection->stop();
// // 					state = DISCONNECT_FINISHED;
// // 				}
// // 				break;

// // 				case CONNECTED: {
// // 					if (ack == 0) {
// // 						connection->sendMessage("OSG/1.0:SYN\n\0");
// // 						state = RECEIVE_ACK;
// // 					}
					

					
// // 				}
// // 				break;

				
// // 			}
// // 		}
// 	}

};

#endif /* ARDUINOCONNECTOR_H */