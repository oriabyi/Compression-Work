# include "../includes/general.hpp"
# include "../../serverDir/includes/Server.Class.hpp"

int							checkIO(ssize_t len, boost::system::error_code error)
{
	if (len == ERROR_IO)
		return (ERROR_IO);
	else if (error == boost::asio::error::eof)
		return (EOF);
	else if (error)
		throw boost::system::system_error(error);
	return (0);
}

int							areNumbers(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

size_t						numLen(int numb)
{
	size_t					lenNumber;
	
	lenNumber = 1;
	if (numb < 0)
		lenNumber++;
	while (numb /= 10)
		lenNumber++;
	return (lenNumber);
}

