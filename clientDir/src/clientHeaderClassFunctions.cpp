# include "../includes/Client.Class.hpp"

void						Client::getHeader(class Client *client, boost::asio::ip::tcp::socket *socket)
{
	ssize_t					tempElementOfHeader;

	try
	{
		tempElementOfHeader = 0;
		readSafe(socket, &tempElementOfHeader, sizeof(client->getMagicValue()));
		client->setMagicValue((int)tempElementOfHeader);

		tempElementOfHeader = 0;
		readSafe(socket, &tempElementOfHeader, sizeof(client->getLength()));
		client->setLength((short)tempElementOfHeader);

		tempElementOfHeader = 0;
		readSafe(socket, &tempElementOfHeader, sizeof(client->getRequestCode()));
		client->setRequestCode((short)tempElementOfHeader);
	}
	catch (std::exception &ex)
	{
		std::cerr << "Client ERROR: " << ex.what() << "!\n";
	}
}

void						Client::sendHeader(class Client *client, boost::asio::ip::tcp::socket *socket)
{
	try
	{
		sendElem(socket, client->getMagicValue());
		sendElem(socket, client->getLength());
		sendElem(socket, client->getRequestCode());
	}
	catch (std::exception &ex)
	{
		std::cerr << "Client ERROR: " << ex.what() << "!\n";
	}
}
