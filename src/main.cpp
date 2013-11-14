#include <map>
#include <string>
#include <iostream>

#include "Publisher.hpp"


//int main(void)
//{
//	std::map<std::string, PubSub::SubjectBase> test;
//
//	PubSub::Subject<void (void)> sub1;
//	PubSub::Subject<void (int&, float)> sub2;
//
//	test.insert(std::make_pair("sub1", sub1));
//	test.insert(std::make_pair("sub2", sub2));
//
//	auto l1 = sub1.registerObserver([] (void)
//	{
//		std::cout << "coucou" << std::endl;
//	});
//
//	auto l2 = sub2.registerObserver([] (int &a, float b)
//	{
//		std::cout << "lol : " << a << " hahaha " << b << std::endl;
//		a = 24;
//	});
//
//	int a = 0;
//
//	sub1();
//	sub2(a, 4.1);
//}


int main(void)
{
	IData *f = new Data<float>(0.42f);
	static_cast<Data<float>*>(f)->data = 10.0f;
	Data<float> *convertedF = static_cast<Data<float>*>(f);

	Any g = 1212;

	int h = g;

	g = 4242;

	int gValue = g;

	return 0;
}