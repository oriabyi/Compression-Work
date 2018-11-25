# include "../includes/Server.Class.hpp"


void							Server::getElement(class Server *server, boost::asio::ip::tcp::socket *socket, size_t *magic, size_t bytes)
{
	ssize_t						lenMessage;
	*magic = 0;

	lenMessage = readSafe(socket, magic, bytes);
	server->setBytesReceived((unsigned)(server->getBytesReceived() + lenMessage));
}

short 							Server::getCheckHeader(class Server *server, boost::asio::ip::tcp::socket *socket)
{
	size_t						magic;

	try
	{
		getElement(server, socket, &magic, sizeof(int));
		if (magic != MAGIC_VALUE)
			return  (WRONGMAGICVALUE_RQ);
		server->setMagicValue((int)magic);

		getElement(server, socket, &magic, sizeof(short));
		if (magic > BUFFER_SIZE)
			return (WRONGLENGHT_RQ);
		server->setLength((short)magic);

		getElement(server, socket, &magic, sizeof(short));
		if (magic < 1 || magic > 4)
		{
			std::cout << "ERORR\n";
			return (WRONGREQUESCODE_RQ);
		}
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
