# include "../includes/Stats.Class.hpp"

Stats::Stats()
{
	this->bytesReceived = 0;
	this->bytesSent = 0;
	this->compressionRate = 0;
}

unsigned int	Stats::getBytesReceived() const
{
	return (this->bytesReceived);
}

unsigned int	Stats::getBytesSent() const
{
	return (this->bytesSent);
}

uint8_t			Stats::getCompressionRate() const
{
	return (this->compressionRate);
}

void			Stats::setBytesReceived(unsigned int bytesSent)
{
	this->bytesReceived = bytesSent;
}

void			Stats::setBytesSent(unsigned int bytesSent)
{
	this->bytesSent = bytesSent;
}

void			Stats::setCompressionRate(uint8_t compressionRate)
{
	this->compressionRate = compressionRate;
}
