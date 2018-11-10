#ifndef CLIENT_TEST_GENERAL_HPP
# define CLIENT_TEST_GENERAL_HPP

# include <thread>
# include <stdlib.h>
# include <string.h>
# include <iostream>
# include <boost/asio.hpp>

#include <iostream>
#include <cstring>

# include "../../generalDir/includes/Header.Class.hpp"
# include "../../generalDir/includes/Stats.Class.hpp"

# define PING				1
# define GET_STATS			2
# define RESET_STATS		3
# define COMPRESS			4

# define BUFFER_SIZE		32767
# define MAGIC_VALUE		0x53545259

# define ERROR_IO			0


char						*ft_itoa(int number);
int							areNumbers(char *str);
char						*ft_strnew(size_t size);
int							checkIO(ssize_t len, boost::system::error_code error);

template <typename T>
ssize_t						writeSafe(boost::asio::ip::tcp::socket *socket, T *data, size_t bytes)
{
	ssize_t 	lenMessage;
	boost::system::error_code error;

	lenMessage = socket->write_some(boost::asio::buffer(data, bytes), error);
	if (checkIO(lenMessage, error) == EOF)
		return (0);
	return (lenMessage);
}

template <typename T>
ssize_t 					readSafe(boost::asio::ip::tcp::socket *socket, T *data, size_t bytes)
{
	ssize_t 	lenMessage;
	boost::system::error_code error;

	lenMessage = socket->read_some(boost::asio::buffer(data, bytes), error);
	if (checkIO(lenMessage, error) == EOF)
		return (0);
	return (lenMessage);
}

template  <typename T>
ssize_t						sendElem(boost::asio::ip::tcp::socket *socket, T data)
{
	return (writeSafe(socket, &data, sizeof(data)));
}

#endif
