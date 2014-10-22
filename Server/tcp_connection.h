

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "tcp_connection.h"


//#include "../Arduino/ProgramController.h"
using boost::asio::ip::tcp;
class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void sendMessage(std::string message_in) {
    std::cout << "Sending: ";
    std::cout << message_in << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(message_in),
          boost::bind(&tcp_connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
  }



  string receive_command()
  {
    
    

    boost::asio::streambuf in_stream;
    
    // reserve 512 bytes in output sequence
    boost::asio::streambuf::mutable_buffers_type bufs = in_stream.prepare(128);


    boost::asio::socket_base::bytes_readable command(true);
    
    socket_.io_control(command);
    
    std::size_t bytes_readable = command.get();
    // if (bytes_readable == 0) {
    //   return "";
    // }
    // std::cout << "bytes_readable: " << bytes_readable << std::endl;

    

    size_t n = socket_.receive(bufs);

    

    in_stream.commit(n);

    std::istream is(&in_stream); //stream into buffer
    std::string s; //output string

    is >> s; //write stream into string

    std::string response = s;
    //std::string response = "hello world";
    // std::string response = ProgramController::getInstance()->run(s);

    return response;
  }

  void ack_command_received(string sendstr) {
    boost::asio::streambuf outstream;
    std::ostream os(&outstream);
    
    if (sendstr.compare("exit") == 0) {
      os << "You are exiting, I'll wait for a new connection. Goodbye!" << endl;
    } else {

    }

    os << sendstr << endl;
    size_t n2 = socket_.send(outstream.data());
    outstream.consume(n2);
  }

  void stop() {
    socket_.close();
  }

private:
  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
};
#endif /* TCP_CONNECTION_H */