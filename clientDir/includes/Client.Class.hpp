#ifndef WORK_CLIENT_CLASS_HPP
# define WORK_CLIENT_CLASS_HPP

# include "../../generalDir/includes/general.hpp"

class						Client : protected Header, protected Stats
{
public:
	Client();
	Client(boost::asio::io_service &io_service, char **av);
	~Client() = default;

protected:
	static void				getSendMessage(class Client *client, boost::asio::ip::tcp::socket *socket);

	static void				initHeader(class Client *client, char *requestCode);
	static void				sendHeader(class Client *client, boost::asio::ip::tcp::socket *socket);
	static void 			getHeader(class Client *client, boost::asio::ip::tcp::socket *socket);
	
	static void				getStats(class Client *client, boost::asio::ip::tcp::socket *socket);
};
#endif
