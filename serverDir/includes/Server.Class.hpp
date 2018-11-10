#ifndef SERVER_TEST_SERVERCLASS_HPP
# define SERVER_TEST_SERVERCLASS_HPP

# include "../../generalDir/includes/general.hpp"

# define	OK_RQ				0
# define	ERROR_RQ			1
# define	WRONGLENGHT_RQ		2
# define	WRONGREQUESCODE_RQ	3
# define	WRONGMAGICVALUE_RQ	33

# define	CONTAINS_NUMBERS	34
# define	CONTAINS_UPPER		35
# define	CONTAINS_BAD_CHARS	36
# define	EMPTY_STRING		37

# define	COMPRESSION_RATE(x, y) (uint8_t)(100 * ((double)x / (double)y))

class 							Server : protected Header, protected Stats
{
public:
	Server();
	Server(boost::asio::io_service &io_service, unsigned short port);
	~Server() = default;
	
protected:
	static void					session(boost::asio::ip::tcp::socket socket);
	
	static short				getCheckHeader(class Server *server, boost::asio::ip::tcp::socket *socket);
	static void					sendHeader(class Server *server, boost::asio::ip::tcp::socket *socket);
	
	static void 				ping_Request(class Server *server, boost::asio::ip::tcp::socket *socket);
	static void 				getStats_Request(class Server *server, boost::asio::ip::tcp::socket *socket);
	static void 				resetStats_Request(class Server *server, boost::asio::ip::tcp::socket *socket);
	static void 				compression_Request(class Server *server, boost::asio::ip::tcp::socket *socket);
	
	static void					sendStats(class Server *server, boost::asio::ip::tcp::socket *socket);
	
	static void 				errorGot(class Server *server, boost::asio::ip::tcp::socket *socket, short errorCode);
};

char							*algCompresss(char *str, short *requestCode);

#endif
