#include "stdafx.h"
#include "NetworkClient.h"

//http://thisthread.blogspot.co.uk/search/label/ASIO

NetworkClient::NetworkClient()
{
}




NetworkClient::~NetworkClient()
{
}

struct ClientConnection
{
	boost::asio::io_service& io_service;
	boost::asio::ip::tcp::socket socket;

	ClientConnection(boost::asio::io_service& svc, std::string const& host, std::string const& port)
		: io_service(svc), socket(io_service)
	{
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query(host, port));
		boost::asio::connect(this->socket, endpoint);
	};

	void send(std::string const& message) {
		socket.send(boost::asio::buffer(message));
	}
};
