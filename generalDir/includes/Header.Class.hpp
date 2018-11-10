#ifndef WORK_HEADER_HPP
# define WORK_HEADER_HPP

class						Header
{
private:
	int						magicValue;
	short					length;
	short					requestCode;
public:
	Header();
	~Header() = default;

	int						getMagicValue() const;
	short					getLength() const;
	short					getRequestCode() const;

	void					setMagicValue(int magicValue);
	void					setLength(short length);
	void					setRequestCode(short requestCode);
};

#endif
