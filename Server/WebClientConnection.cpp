#include "WebClientConnection.h"

WebClientConnection::pointer WebClientConnection::create(boost::asio::io_service& io_service)
  	{
    	return pointer(new WebClientConnection(io_service));
  	}

void WebClientConnection::sendMessage(std::string message_in) {
	std::cout << "Sending: ";
	std::cout << message_in << std::endl;
	
	boost::asio::async_write(socket_, boost::asio::buffer(message_in),
        boost::bind(&WebClientConnection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

tcp::socket& WebClientConnection::socket() {
    return socket_;
}

void WebClientConnection::handle_write(const boost::system::error_code&, size_t /*bytes_transferred*/) {
	
}