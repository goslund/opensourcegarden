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


	}

};



#endif /* WEBClIENTSERVER_H */
