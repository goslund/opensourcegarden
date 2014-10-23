#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/lambda/if.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include "UDPParser.h"

#define OSG_PORT 8102
std::string large_string;
std::string make_daytime_string()
{
  for (int i=0; i < 65000; i++)
  {
    large_string = large_string + "1";
  }
  return "";
}
using namespace boost;
using boost::asio::ip::udp;
class udp_server
{
public:
  udp_server(boost::asio::io_service& io_service)
    : socket_(io_service, udp::endpoint(udp::v4(), OSG_PORT))
	{
    	start_receive();
	}

	


private:
	void start_receive() {
		
    	socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));

  	}

  	void handle_receive(const boost::system::error_code& error,
      std::size_t bytes_transferred)
  	{
      
      //std::cout << "Hello World" << std::endl;
      //std::cout << bytes_transferred << std::endl;
      if (bytes_transferred != 128 && bytes_transferred != 0) {
        //UDPParser* udp_message_parser = new udp_message_parser();
        std::cout.write(recv_buffer_.data(), bytes_transferred);
  		  //std::cout.write("Hello World", 11);
        std::cout << std::endl;
  		  //boost::array<char, 128> buf;
        //boost::system::error_code error2;

      //size_t len = socket_.read_some(boost::asio::buffer(buf), error2);

    	if (!error || error == boost::asio::error::message_size)
    	{
      		boost::shared_ptr<std::string> message(
          new std::string(make_daytime_string()));

          std::cout << message << std::endl;

      socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
          boost::bind(&udp_server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));


        
      }

    }
    start_receive();
  }


	void handle_send(boost::shared_ptr<std::string> /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/)
  	{
  	}


	udp::socket socket_;
	udp::endpoint remote_endpoint_;
  	boost::array<char, 128> recv_buffer_;
};