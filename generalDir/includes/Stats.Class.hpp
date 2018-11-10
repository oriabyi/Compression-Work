#ifndef WORK_STATS_HPP
# define WORK_STATS_HPP

# include <cstdlib>

class						Stats
{
private:
	unsigned int			bytesReceived;
	unsigned int			bytesSent;
	uint8_t					compressionRate;

public:
	Stats();
	~Stats() = default;

	unsigned int			getBytesReceived() const;
	unsigned int			getBytesSent() const;
	uint8_t					getCompressionRate() const;

	void					setBytesReceived(unsigned int bytesSent);
	void					setBytesSent(unsigned int bytesSent);
	void					setCompressionRate(uint8_t compressionRate);
};

#endif
