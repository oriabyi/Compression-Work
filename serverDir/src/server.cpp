# include "../includes/Server.Class.hpp"

int									main(int ac, char **av)
{
	try
	{
		if (ac != 2)
			throw std::logic_error("usage: ./server port");
		else if (av[1][0] == '-')
			throw std::logic_error("port can not be signed!");
		else if (areNumbers(av[1]))
			throw std::logic_error("port has to contain ONLY numbers!");
	}
	catch (std::exception &ex)
	{
		std::cerr << "Server ERROR: " << ex.what() << std::endl;
		return (1);
	}
	
	try
	{
		boost::asio::io_service		io_service;
		class Server				server(io_service, ((unsigned short)std::strtol(av[1], nullptr, 10)));
	}
	catch (std::exception &ex)
	{
		std::cerr << "Server ERROR: " << ex.what() << "!\n";
	}
	
	return (0);
}