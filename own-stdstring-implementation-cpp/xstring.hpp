#ifndef XSTRING_HPP
#define XSTRING_HPP

#include <iostream>
#include <exception>
#include <initializer_list>
#include <vector>
#include <algorithm>

using uint = std::uint64_t;
using ilChar = std::initializer_list<const char*>;
using pairCharInt = std::pair<char*, uint>;



class xString;

std::ostream& operator<< (std::ostream&, const xString&);


class xString
{
private:
	pairCharInt alloc(std::vector<const char*>, std::vector<uint> = {}) const;

public:
	xString();
	xString(const char* str);
	xString(const xString& obj);
	xString(xString&& obj) noexcept;

	xString& operator= (const xString& obj);
	xString& operator= (xString && obj) noexcept;

	virtual ~xString();

	friend std::ostream& operator<< (std::ostream&, const xString&);
	uint size() const noexcept;

	xString& operator+=(const xString& obj);

//private:
	char* m_string {nullptr};
	uint m_size {0};

	
};

#endif // !XSTRING_HPP
