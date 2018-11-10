# include "../includes/Client.class.hpp"

Client::Client()
{
	this->setMagicValue(MAGIC_VALUE);
}

void							Client::initHeader(class Client *client, char *requestCode)
{
	client->setMagicValue(MAGIC_VALUE);
	client->setLength(0);
	client->setRequestCode((short)(std::strtol(requestCode, nullptr, 10)));
}

void							Client::getSendMessage(class Client *client, boost::asio::ip::tcp::socket *socket)
{
	std::string					message;
	ssize_t						lenMessage;
	boost::system::error_code	error;
	
	std::cout << "Enter message: ";
	std::getline(std::cin, message);
	client->setLength((short)message.length());
	client->sendHeader(client, socket);
	try
	{
		lenMessage = socket->write_some(boost::asio::buffer(message, message.length()), error);
		if (checkIO(lenMessage, error) == EOF)
			return ;
	}
	catch (std::exception &ex)
	{
		std::cerr << ex.what();
	}
}

void							Client::getStats(class Client *client, boost::asio::ip::tcp::socket *socket)
{
	ssize_t						tempElementOfHeader;
	
	try
	{
		tempElementOfHeader = 0;
		readSafe(socket, &tempElementOfHeader, sizeof(client->getBytesReceived()));
		client->setBytesReceived((unsigned)tempElementOfHeader);
		
		tempElementOfHeader = 0;
		readSafe(socket, &tempElementOfHeader, sizeof(client->getBytesSent()));
		client->setBytesSent((unsigned)tempElementOfHeader);
		
		
		tempElementOfHeader = 0;
		readSafe(socket, &tempElementOfHeader, sizeof(client->getCompressionRate()));
		client->setCompressionRate((uint8_t)tempElementOfHeader);
	}
	catch (std::exception &ex)
	{
		std::cout << "Client ERROR: " << ex.what() << "!\n";
	}
}

Client::Client(boost::asio::io_service &io_service, char **av)
{
	class Client						client;
	int									tempRequestCode;
	boost::system::error_code			error;
	boost::asio::ip::tcp::socket		socket(io_service);
	boost::asio::ip::tcp::resolver		resolver(io_service);

	boost::asio::connect(socket, resolver.resolve({av[1], av[2]}));

	client.initHeader(&client, av[3]);
	
	if (client.getRequestCode() == COMPRESS)
		client.getSendMessage(&client, &socket);
	else
		client.sendHeader(&client, &socket);

	tempRequestCode = client.getRequestCode();

	client.getHeader(&client, &socket);
	
	if (tempRequestCode == GET_STATS)
	{
		client.getStats(&client, &socket);
	}
	else if (tempRequestCode == COMPRESS)
	{
		char 	buf[BUFFER_SIZE];
		
		try
		{
			if (checkIO(socket.read_some(boost::asio::buffer(buf), error), error) == EOF)
				std::cerr << "Client ERROR: with reading by socket!\n";
		}
		catch (std::exception &ex)
		{
			std::cerr << "Client ERROR: EOF!\n";
		}
	}
	if (socket.is_open())
	{
		socket.close();
	}
}

