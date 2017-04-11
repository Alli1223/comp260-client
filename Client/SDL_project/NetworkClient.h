#pragma once
#include "stdafx.h"
#include "NetworkClient.h"




class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();

	void NetworkClient::NetworkUpdate();
	void NetworkClient::sendTCPMessage(std::string host, int port, std::string message);

	void NetworkClient::RecieveMessage();

	struct Client
	{
		boost::asio::io_service& io_service;
		boost::asio::ip::tcp::socket socket;

		Client(boost::asio::io_service& svc, std::string const& host, std::string const& port)
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

	
};

