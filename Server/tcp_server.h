#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "tcp_connection.h"

#include <stdio.h>
//using namespace std;
class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8102))
  {
    try {
      start_accept();
    } catch(...) {
     std::cout << "Unknown Exception" << std::endl;
    }
  }

private:
  void start_accept()
  {
    
      new_connection =
      tcp_connection::create(acceptor_.get_io_service());


    // boost::thread connection_thread(&this->handle_accept(new_connection, boost::asio::placeholders::error);
    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
    
  }

  void handle_accept(tcp_connection::pointer new_connection,
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

  tcp::acceptor acceptor_;
  tcp_connection::pointer new_connection;
};

