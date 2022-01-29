#include <iostream>
#include "xstring.hpp"

auto main() -> int
{
	auto txt = "works amlost perfectly..";
	xString a(txt);
	xString b(a);

	std::cout << a << "\n" << &a << "\n" << a.size() << "\n\n";
	std::cout << b << "\n" << &b << "\n" << b.size() << "\n\n";

	return 0;
}
