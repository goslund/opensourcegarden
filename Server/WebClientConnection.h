#ifndef WEBCLIENTCONNECTION_H
#define WEBCLIENTCONNECTION_H
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <string.h>
#include "tcp_connection.h"

using boost::asio::ip::tcp;

class WebClientConnection : public boost::enable_shared_from_this<WebClientConnection> {
public:

	typedef boost::shared_ptr<WebClientConnection> pointer;

    static pointer create(boost::asio::io_service& io_service);
    void sendMessage(std::string message_in);
    tcp::socket& socket();  	
private:
  WebClientConnection(boost::asio::io_service& io_service): socket_(io_service)
  	{
  	}

  void handle_write(const boost::system::error_code&, size_t /*bytes_transferred*/);

  tcp::socket socket_;
  std::string message_;

};


#endif /* WEBCLIENTCONNECTION_H */