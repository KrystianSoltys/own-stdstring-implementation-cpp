#ifndef XSTRING_HPP
#define XSTRING_HPP

#include <ostream>
#include <exception>

class xString;

std::ostream& operator<< (std::ostream&, const xString&);


class xString
{
private:
	std::pair<char*, std::uint64_t> 
		alloc(const char* ptr, std::uint64_t sz = 0) const;

public:
	xString();
	xString(const char* str);
	xString(const xString& obj);
	xString(xString&& obj) noexcept;

	xString& operator= (const xString& obj);
	xString& operator= (xString && obj) noexcept;

	virtual ~xString();

	friend std::ostream& operator<< (std::ostream&, const xString&);
	std::uint64_t size() const noexcept;

private:
	char* m_string {nullptr};
	std::uint64_t m_size {0};

	
};

#endif // !XSTRING_HPP
