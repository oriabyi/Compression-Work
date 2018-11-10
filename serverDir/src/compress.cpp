# include "../includes/Server.Class.hpp"
# include "../../generalDir/includes/general.hpp"

int							countChars(const char *str, char c)
{
	int     				counter;
	
	counter = 0;
	if (str == nullptr)
		return (0);
	while (str[counter] && str[counter] == c)
		counter++;
	return (counter);
}

int							checkStr(char *str, char **buffer, short *requestCode)
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
	*buffer = nullptr;
	return (1);
}

char						*algCompresss(char *str, short *requestCode)
{
	char					temp;
	int						numOfChars;
	char					*buffer;
	char					*tempNum;
	
	if (checkStr(str, &buffer, requestCode) == 1)
		return (buffer);
	buffer = ft_strnew(std::strlen(str));
	while (*str)
	{
		temp = *str;
		numOfChars = countChars(str, *str);
		if (numOfChars > 2)
		{
			tempNum = ft_itoa(numOfChars);
			strncat(tempNum, str, 1);
			strcat(buffer, tempNum);
			str += numOfChars;
			free(tempNum);
		}
		else
		{
			while (*str && *str == temp)
			{
				if (*str != '\n')
					strncat(buffer, str, 1);
				str++;
			}
		}
	}
	strcat(buffer, "\0");
	return (buffer);
}
