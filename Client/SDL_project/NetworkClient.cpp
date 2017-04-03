#include "stdafx.h"
#include "NetworkClient.h"



NetworkClient::NetworkClient()
{
}


NetworkClient::~NetworkClient()
{
}

void NetworkClient::sendTCPMessage(std::string host, int port, std::string message)
{
	boost::asio::io_service ios;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

	boost::asio::ip::tcp::socket socket(ios);

	socket.connect(endpoint);

	boost::array<char, 128> buf;
	for (int i = 0; i < message.size(); i++)
		buf[i] = message[i];
	boost::system::error_code error;
	socket.write_some(boost::asio::buffer(buf, message.size()), error);
	socket.close();
}

void NetworkClient::RecieveMessage()
{
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::array<char, 128> data;
	socket.receive(boost::asio::buffer(data, data.size()));
	std::cout << data[0] << std::endl;
}