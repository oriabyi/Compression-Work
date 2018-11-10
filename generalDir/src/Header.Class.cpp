# include "../includes/Header.Class.hpp"

Header::Header()
{
	this->magicValue = 0;
	this->length = 0;
	this->requestCode = 0;
}

int				Header::getMagicValue() const
{
	return (this->magicValue);
}

short			Header::getLength() const
{
	return (this->length);
}

short			Header::getRequestCode() const
{
	return (this->requestCode);
}

void			Header::setMagicValue(int magicValue)
{
	this->magicValue = magicValue;
}

void			Header::setLength(short length)
{
	this->length = length;
}

void			Header::setRequestCode(short requestCode)
{
	this->requestCode = requestCode;
}
