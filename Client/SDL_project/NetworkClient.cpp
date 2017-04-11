#include "stdafx.h"
#include "NetworkClient.h"

//http://thisthread.blogspot.co.uk/search/label/ASIO

NetworkClient::NetworkClient(boost::asio::io_service ios)
{
}


NetworkClient::~NetworkClient()
{
}

void server_thread() {
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 2222));

		{
			boost::asio::ip::tcp::socket socket(io_service);
			acceptor.accept(socket);

			boost::asio::streambuf streamBuffer;
			boost::system::error_code errorCode;
			while (boost::asio::read(socket, streamBuffer, errorCode)) {
				std::cout << "received: '" << &streamBuffer << "'\n";

				if (errorCode) {
					std::cout << "status: " << errorCode.message() << "\n";
					break;
				}
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}


// Update every frame
void NetworkClient::NetworkUpdate()
{

	// Create a new TCP listener thread
	//std::thread ServerThread(server_thread);
	//ServerThread.get_id();
	
	//server_thread();
}

void NetworkClient::sendTCPMessage(std::string host, int port, std::string message)
{
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

	boost::asio::ip::tcp::socket socket(ios);

	socket.connect(endpoint);

	boost::array<char, 128> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}
	
	boost::system::error_code error;
	socket.write_some(boost::asio::buffer(buf, message.size()), error);
	socket.send(boost::asio::buffer(buf, message.size()));
	std::cout << "Message: " << message << " sent." << std::endl;
	socket.close();
}



void NetworkClient::RecieveMessage()
{
	
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::array<char, 128> data;
	try
	{
		for (;;)
		{
			std::array<char, 128> buf;
			boost::system::error_code error;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer
			else if (error)
				throw boost::system::system_error(error);

			std::cout.write(buf.data(), len);
			std::cout << '|';
		}
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		//std::cerr << e.what() << std::endl;
	}
}