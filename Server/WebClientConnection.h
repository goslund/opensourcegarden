#ifndef WEBCLIENTCONNECTION_H
#define WEBCLIENTCONNECTION_H

using boost::asio::ip::tcp;

class WebClientConnection : public boost::enable_shared_from_this<WebClientConnection> {
	typedef boost::shared_ptr<WebClientConnection> pointer;

    static pointer create(boost::asio::io_service& io_service)
  	{
    	return pointer(new WebClientConnection(io_service));
  	}
};


#endif /* WEBCLIENTCONNECTION_H */