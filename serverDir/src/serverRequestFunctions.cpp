# include "../includes/Server.Class.hpp"

void 	Server::ping_Request(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	server->setRequestCode(OK_RQ);
	sendHeader(server, socket);
}

void 	Server::getStats_Request(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	server->setRequestCode(OK_RQ);
	sendHeader(server, socket);
	sendStats(server, socket);
}

void							Server::resetStats_Request(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	server->setRequestCode(OK_RQ);
	
	server->setBytesReceived(0);
	server->setBytesSent(0);
	server->setCompressionRate(0);
	
	sendHeader(server, socket);
}

void							Server::compression_Request(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	boost::system::error_code	error;
	char						data[BUFFER_SIZE];
	short						tempRequestCode;
	char 						*buf;
	ssize_t						lenMessage;
	
	try
	{
		readSafe(socket, data,(size_t)server->getLength());
		tempRequestCode = OK_RQ;
		if ((buf = algCompresss(data, &tempRequestCode)))
		{
			server->setLength((short) (std::strlen(buf)));
			if (tempRequestCode == OK_RQ)
				server->setCompressionRate(COMPRESSION_RATE(server->getLength(), strlen(data)));
			server->setRequestCode(tempRequestCode);
		} else
		{
			server->setLength(0);
		}
		server->sendHeader(server, socket);
		if (buf)
		{
			lenMessage = boost::asio::write(*socket, boost::asio::buffer(buf, (size_t)(server->getLength())), error);
			if (checkIO(lenMessage, error) == EOF)
				return ;
			server->setBytesSent(server->getBytesSent() + (unsigned)lenMessage);
		}
		free(buf);
	}
	catch (std::exception &ex)
	{
		std::cerr << "Server ERROR: " << ex.what() << "!\n";
		server->setRequestCode(ERROR_RQ);
		server->sendHeader(server, socket);
	}
}
