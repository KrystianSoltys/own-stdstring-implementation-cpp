#include "xstring.hpp"



pairCharInt 
xString::alloc(std::vector<const char*> ptrs, std::vector<uint> sizes) const
{
	const char* ptr = nullptr;

	uint sizesVecLen = sizes.size();
	sizes.resize(ptrs.size()); //both vec have same size
	
	//std::for_each(sizes.begin() + sizesVecLen, sizes.end(), [](auto& x) {x = 0; });
	std::fill(sizes.begin() + sizesVecLen, sizes.end(), 0);

	uint ct = 0;
	for (uint i = 0; i < ptrs.size(); i++)
	{
		if (sizes[i]) continue;
		else
		{
			ct = 0;				//for vec sizes
			ptr = ptrs[i];
			while (*ptr)		//*ptr != '\0'
			{
				ct++;
				ptr++;			//probably not best but didn't find better way
			}
			sizes[i] = ct;
			ct = 0;
		}
	}
	
	uint n = 0;
	for (auto& i : sizes)
	{
		n += i;
	}

	char* toReturnPtr = nullptr;
	try
	{
		toReturnPtr = new char[n + 1]; // additional pos for \0 ending
	}
	catch (std::bad_alloc&)
	{
		toReturnPtr = nullptr;
		n = 0;
		return pairCharInt(toReturnPtr, n);
	}

	uint k = 0;

	uint j = 0;
	for (auto x : ptrs)					//copying
	{
		for (int i = 0; i < sizes[j]; i++)
		{
			toReturnPtr[k++] = x[i];
		}
		j++;
	}

	if(toReturnPtr)
		toReturnPtr[n] = '\0';

	return pairCharInt(toReturnPtr, n);
}


xString::xString()
	:m_string(nullptr), m_size(0)
{
}

xString::xString(const char* str)
{
	auto result = alloc({ str });
	
	m_string = result.first;
	m_size = result.second;
}

xString::xString(const xString& obj)
{
	auto result = alloc({ obj.m_string }, { obj.m_size });

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

	if (m_string) delete[] m_string;
	auto result = alloc({ obj.m_string }, { obj.m_size });

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

uint xString::size() const noexcept
{
	return m_size;
}

xString& xString::operator+=(const xString& obj)
{
	if (!obj.m_size || !obj.m_string) return *this;

	auto result = 
		alloc({ this->m_string, obj.m_string }, { this->m_size, obj.m_size });

	if (m_string)
		delete[] m_string;

	m_string = result.first;
	m_size = result.second;

	return *this;
}



std::ostream& operator<<(std::ostream& os, const xString& obj)
{
	os << obj.m_string;
	return os;
}
