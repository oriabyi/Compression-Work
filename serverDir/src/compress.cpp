# include "../includes/Server.Class.hpp"
# include "../../generalDir/includes/general.hpp"

int									countChars(const char *str, char c)
{
	int     						counter;
	
	counter = 0;
	if (str == nullptr)
		return (0);
	while (str[counter] && str[counter] == c)
		counter++;
	return (counter);
}

int									checkStr(char *str, short *requestCode)
{
	if (str == nullptr || *str == '\0')
	{
		*requestCode = EMPTY_STRING;
		return (1);
	}
	while (*str >= 'a' && *str <= 'z')
		str++;
	if (!*str || *str == '\n')
		return (0);
	else if (isdigit(*str))
	{
		*requestCode = CONTAINS_NUMBERS;
	}
	else if (isupper(*str))
	{
		*requestCode = CONTAINS_UPPER;
	}
	else
	{
		*requestCode = CONTAINS_BAD_CHARS;
	}
	return (1);
}

std::string 						algCompress(char *str, short *requestCode)
{
	char							temp;
	int								numOfChars;
	std::string						result;

	if (checkStr(str, requestCode) == 1)
		return (result);
	while (*str)
	{
		temp = *str;
		numOfChars = countChars(str, *str);
		if (numOfChars > 2)
		{
			result += std::to_string(numOfChars);
			result.push_back(*str);
			str += numOfChars;
		}
		else
		{
			while (*str && *str == temp)
			{
				if (*str != '\n')
					result.push_back(*str);
				str++;
			}
		}
	}
	return (result);
}
