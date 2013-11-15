#include <map>
#include <string>
#include <iostream>

#include "PubSub.hpp"

#include <vector>
#include <string>

struct Test : public PubSub
{
	std::string name;
	void LogInt(int a, int b)
	{
		std::cout << "Test " << name << " log ints : " << a << " " << b << std::endl;
	}
	Test(){}
	virtual ~Test(){}
};

int main(void)
{
	Test test1;
	test1.sub("test", [](int b, float c, bool d)
	{
		std::cout << " " << b << " " << c << " " << d << std::endl;
	});

	test1.pub("test", 42, 12.34f, false);

	Test test2;
	test2.name = "KikooLol";
	test2.sub("testTest", [&](int a, int b)
	{
		test2.LogInt(a, b);
	});
	test2.pub("testTest", 21, 42);
	return 0;
}