#include <map>
#include <string>
#include <iostream>

#include "PubSub.hpp"

#include <vector>
#include <string>

struct Test
{
	std::string name;
	void LogInt(int a, int b)
	{
		std::cout << "Test " << name << " log ints : " << a << " " << b << std::endl;
	}
};

int main(void)
{
	PubSub::getInstance().sub("test", [](int b, float c, bool d)
	{
		std::cout << " " << b << " " << c << " " << d << std::endl;
	});

	PubSub::getInstance().pub("test", 42, 12.34f, false);

	Test test;
	test.name = "KikooLol";
	PubSub::getInstance().sub("testTest", [&](int a, int b)
	{
		test.LogInt(a, b);
	});

	PubSub::getInstance().pub("testTest", 21, 42);
	return 0;
}