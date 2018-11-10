# include "../includes/Server.Class.hpp"

Server::Server()
{
	this->setMagicValue(0);
	this->setLength(0);
	this->setRequestCode(0);

	this->setBytesReceived(0);
	this->setBytesSent(0);
	this->setCompressionRate(0);
}

Server::Server(boost::asio::io_service &io_service, unsigned short port)
{
	this->setMagicValue(0);
	this->setLength(0);
	this->setRequestCode(0);

	this->setBytesReceived(0);
	this->setBytesSent(0);
	this->setCompressionRate(0);
	boost::asio::ip::tcp::acceptor a(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
	while (1)
	{
		boost::asio::ip::tcp::socket socket(io_service);
		a.accept(socket);
		std::thread(session, std::move(socket)).detach();
		if (socket.is_open())
		{
			socket.close();
		}
	}
}

void							Server::sendStats(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	try
	{
		sendElem(socket, server->getBytesReceived());
		sendElem(socket, server->getBytesSent());
		sendElem(socket, server->getCompressionRate());
	}
	catch (std::exception &ex)
	{
		std::cerr << "Client ERROR: " << ex.what() << "!\n";
	}
}

void							Server::errorGot(class Server *server, boost::asio::ip::tcp::socket *socket,
																								short errorCode)
{
	server->setRequestCode(errorCode);
	sendHeader(server, socket);
}

void							Server::session(boost::asio::ip::tcp::socket socket)
{
	static class Server			server;
	short 						checkNum;
	
	try
	{
		if ((checkNum = getCheckHeader(&server, &socket)))
		{
			errorGot(&server, &socket, checkNum);
		}
		else if (server.getRequestCode() == PING)
		{
			ping_Request(&server, &socket);
		}
		else if (server.getRequestCode() == GET_STATS)
		{
			getStats_Request(&server, &socket);
		}
		else if (server.getRequestCode() == RESET_STATS)
		{
			resetStats_Request(&server, &socket);
		}
		else if (server.getRequestCode() == COMPRESS)
		{
			compression_Request(&server, &socket);
		}
	}
	catch (std::exception &ex)
	{
		std::cerr << "Exception in thread: " << ex.what() << std::endl;
	}
}