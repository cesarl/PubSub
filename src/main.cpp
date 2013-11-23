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
	test1.sub("test", [](int a, int b)
	{
		std::cout << " " << a << " " << b << std::endl;
	});

	PubSub::pub("test", 1, 2);

	Test test2;
	test2.name = "KikooLol";
	test2.sub("test", [&](int a, int b)
	{
		test2.LogInt(a, b);
		test2.unsub("test");
	});
	PubSub::clearAll();
	PubSub::pub("test", 3, 4);
	PubSub::pub("test", 5, 6);
	return 0;
}