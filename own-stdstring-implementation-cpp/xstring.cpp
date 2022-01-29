#include "xstring.hpp"

std::pair<char*, std::uint64_t> 
	xString::alloc(const char* str, std::uint64_t sz) const
{
	std::uint64_t n = 0;
	auto ptr = str;

	if (sz) n = sz;
	else
	{
		while (*ptr) //*ptr != '\0'
		{
			n++;
			ptr++;		//probably not best but didn't find better way
		}
	}

	ptr = str;
	char* toReturnPtr = nullptr;
	try 
	{
		 toReturnPtr = new char[n + 1]; // additional pos for \0 ending
	}
	catch (std::bad_alloc&)
	{
		toReturnPtr = nullptr;
		n = 0;
	}

	for (size_t i = 0; i < n; i++)
	{
		toReturnPtr[i] = str[i];
	}
	if(n > 0)
		toReturnPtr[n] = '\0';

	return std::pair<char*, std::uint64_t>(toReturnPtr, n);
}


xString::xString()
	:m_string(nullptr), m_size(0)
{
}

xString::xString(const char* str)
{
	auto result = alloc(str);
	
	m_string = result.first;
	m_size = result.second;
}

xString::xString(const xString& obj)
{
	auto result = alloc(obj.m_string, obj.m_size);

	m_string = result.first;
	m_size = obj.m_size;
}

xString::xString(xString&& obj) noexcept
{
	m_string = obj.m_string;
	m_size = obj.m_size;

	obj.m_string = nullptr;
	obj.m_size = 0;
}

xString& xString::operator=(const xString& obj)
{
	if (this == &obj) return *this;

	auto result = alloc(obj.m_string, obj.m_size);

	m_string = result.first;
	m_size = obj.m_size;

	return *this;
}

xString& xString::operator=(xString&& obj) noexcept
{
	if (this == &obj) return *this;

	if (m_string) delete[] m_string;

	m_string = obj.m_string;
	m_size = obj.m_size;

	obj.m_string = nullptr;
	obj.m_size = 0;

	return *this;
}

xString::~xString()
{
	if(m_string)
		delete[] m_string;
}

std::uint64_t xString::size() const noexcept
{
	return m_size;
}



std::ostream& operator<<(std::ostream& os, const xString& obj)
{
	os << obj.m_string;
	return os;
}
