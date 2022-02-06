#include <iostream>
#include "xstring.hpp"

auto main() -> int
{
	auto txt = "works almo";
	auto txt2 = "st perfectly..";
	xString a(txt);

	std::cout << a << "\n" << &a.m_string << "\n" << a.size() << "\n\n";

	a += txt2;

	std::cout << a << "\n" << &a.m_string << "\n" << a.size() << "\n\n";

	return 0;
}
