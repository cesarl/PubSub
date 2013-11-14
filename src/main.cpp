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

int main(void)
{
	{
		Any g = 1212;
		int h = g;
		g = 4242;
		int gValue = g;
	}
	
	////
	////
	////

	std::vector<Any> vec;
	Any a1 = std::string("lol");
	Any a2 = 42;
	vec.push_back(a1);
	vec.push_back(a2);

	testFunc(vec[0], vec[1]);


	////
	////
	////

	Emitter emitter;
	Subscriber subscriber;

	subscriber.subscribe("key", std::function<void(int, float)>([](int a, float b)
	{
		std::cout << "lol : " << a << " hahaha " << b << std::endl;
	}));

	emitter.emit("key", 21, 42.0f);
	emitter.emit("test", 123, 123);

	return 0;
}