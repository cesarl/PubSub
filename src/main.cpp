#include <map>
#include <string>
#include <iostream>

#include "PubSub.hpp"

#include <vector>
#include <string>

void testFunc(const std::string &a, int b)
{
	std::cout << a << " et " << b << std::endl;
}

class Test
{
public:
	void testFunc(unsigned int a, bool b, const std::string &c)
	{
		std::cout << "member testfunc said : " << a << " " << b << " " << c << std::endl;
	}
	float testFunc2(bool b, const std::string &c)
	{
		std::cout << "member testfunc said :" << " " << b << " " << c << std::endl;
		return 12.0f;
	}
};


using namespace std::placeholders;

int main(void)
{

	PubSub::getInstance().subscribe(std::shared_ptr<Any>(new Any(std::function<void(const std::string &, int)>(
		[](const std::string &a, int b)
	{
		std::cout << "lol : " << a << " and : " << b << std::endl;
	}
	))), "test1");

	Test classTest;

	std::shared_ptr<Any> t(new Any(std::bind(&Test::testFunc, &classTest, _1, _2, _3)));
	PubSub::getInstance().subscribe(t, "test2");

	PubSub::getInstance().publish("test1", std::string("coucou !"), 21);
//	PubSub::getInstance().publish("test2", 42, false, std::string("Ho yeah !"));

	MyListener mylistener;

	PubSub::getInstance().sub("sub1", &MyListener::visit, &mylistener);
	PubSub::getInstance().pub("sub1", 42, false, 42.42f);

	return 0;
}