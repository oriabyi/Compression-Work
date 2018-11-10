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

char						*ft_strnew(size_t size)
{
	char					*ret;
	
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
		return (nullptr);
	return ((char *)std::memset(ret, 0, size + 1));
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

char						*ft_itoa(int number)
{
	char					*ret;
	ssize_t					ssizetNumber;
	size_t					lenght;

	lenght = numLen(number);
	if (!(ret = ft_strnew(lenght)))
		return (nullptr);
	ssizetNumber = (ssize_t)number;
	if (ssizetNumber < 0)
	{
		ret[0] = '-';
		ssizetNumber = -ssizetNumber;
	}
	ret[--lenght] = (char)(ssizetNumber % 10 + '0');
	while (ssizetNumber /= 10)
		ret[--lenght] = (char)(ssizetNumber % 10 + '0');
	return (ret);
}
