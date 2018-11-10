# include "../includes/Server.Class.hpp"

short 							Server::getCheckHeader(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	size_t						magic;
	ssize_t						lenMessage;
	
	try
	{
		magic = 0;
		lenMessage = readSafe(socket, &magic, sizeof(int));
		server->setBytesReceived((unsigned)(server->getBytesReceived() + lenMessage));
		if (magic != MAGIC_VALUE)
			return  (WRONGMAGICVALUE_RQ);
		server->setMagicValue((int)magic);
		
		
		magic = 0;
		lenMessage = readSafe(socket, &magic, sizeof(short));
		server->setBytesReceived((unsigned)(server->getBytesReceived() + lenMessage));
		if (magic > BUFFER_SIZE)
			return (WRONGLENGHT_RQ);
		server->setLength((short)magic);
		
		
		magic = 0;
		lenMessage = readSafe(socket, &magic, sizeof(short));
		server->setBytesReceived((unsigned)(server->getBytesReceived() + lenMessage));
		if (magic < 1 || magic > 4)
			return (WRONGREQUESCODE_RQ);
		server->setRequestCode((short)magic);
	}
	catch (std::exception &ex)
	{
		std::cerr << "Server ERROR: " << ex.what() << "!\n";
	}
	return (0);
}

void							Server::sendHeader(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	try
	{
		server->setBytesSent((unsigned)(server->getBytesReceived() + sendElem(socket, server->getMagicValue())));
		server->setBytesSent((unsigned)(server->getBytesReceived() + sendElem(socket, server->getLength())));
		server->setBytesSent((unsigned)(server->getBytesReceived() + sendElem(socket, server->getRequestCode())));
	}
	catch (std::exception &ex)
	{
		std::cerr << "Server ERROR: " << ex.what() << "!\n";
	}
}
