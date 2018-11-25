# include "../includes/Client.Class.hpp"
# include "../../generalDir/includes/general.hpp"

int									checkArguments(int ac, char **av)
{
	try
	{
		if (ac == 0 || av == nullptr)
			throw std::logic_error("Client: there is a problem with environment!\n");
		else if (ac != 4)
			throw std::logic_error("Client usage: ./client hostname port requestCode\n");
		else if (areNumbers(av[2]))
			throw std::logic_error("Client: port has to contain only numbers!\n");
		else if (areNumbers(av[3]))
			throw std::logic_error("Client: requestCode has to contain only numbers!\n");
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
		return (1);
	}
	return (0);
}

int									main(int ac, char **av)
{
	try
	{
		if (checkArguments(ac, av))
		{
			return (1);
		}

		boost::asio::io_service		io_service;
		class Client				client(io_service, av);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return (0);
}
