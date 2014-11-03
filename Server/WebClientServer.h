#ifndef WEBClIENTSERVER_H
#define WEBClIENTSERVER_H value

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <stdio.h>
#include "WebClientConnection.h"

class WebClientServer  {
public:
	WebClientServer(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 8103))
	{
	    try {
		    start_accept();
	    } catch(...) {
	     	std::cout << "Unknown Exception" << std::endl;
	    }
  	}

private:
	tcp::acceptor acceptor_;
  	WebClientConnection::pointer new_connection;

	void start_accept() {
	new_connection = WebClientConnection::create(acceptor_.get_io_service());

	acceptor_.async_accept(new_connection->socket(),
        boost::bind(&WebClientServer::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
    
	}

	void handle_accept(WebClientConnection::pointer new_connection,
      const boost::system::error_code& error)
	  {
	    try {
	      	new_connection->sendMessage("Hello World...");
	      	if (!error)
	      	{
		        std::cout << "graph goes here" << std::endl;
		        // ArduinoConnector* connector = new ArduinoConnector(new_connection);
		        // boost::thread t(boost::bind(&ArduinoConnector::loop, connector));
	        	std::cout << "thread started for ArduinoConnector" << std::endl;
	      	}
	      	start_accept();
	    } catch (const std::exception& e) {
	        std::cout << "hwstr" << e.what() << std::endl;
	    }
	 }

};



#endif /* WEBClIENTSERVER_H */
