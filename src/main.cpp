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

	test1.pub("test", 1, 2);

	Test test2;
	test2.name = "KikooLol";
	test2.sub("test", [&](int a, int b)
	{
		test2.LogInt(a, b);
		test2.unsub("test");
	});
	PubSub::clearAll();
	PubSub::broadcast("test", 3, 4);
	PubSub::broadcast("test", 5, 6);
	return 0;
}


//#include <iostream>
//#include <string>
//#include <unordered_map>
//
//#include <functional>
//#include <stdexcept>
//#include <typeinfo>
//#include <memory>
//
//template <typename Lambda>
//struct FunctionHelper
//  : public FunctionHelper<decltype(&Lambda::operator())>
//{};
//
//template <typename ClassType, typename ReturnType, typename... Args>
//struct FunctionHelper<ReturnType(ClassType::*)(Args...) const> {
//  typedef ReturnType (*pointer)(Args...);
//  typedef std::function<ReturnType(Args...)> function;
//};
//
//template <typename Lambda>
//typename FunctionHelper<Lambda>::pointer makeFunctionPtr(Lambda& lambda) {
//  return static_cast<typename FunctionHelper<Lambda>::pointer>(lambda);
//}
//
//template <typename Lambda>
//typename FunctionHelper<Lambda>::function makeFunction(Lambda& lambda) {
//  return static_cast<typename FunctionHelper<Lambda>::function>(lambda);
//}
//
//class Function {
//public:
//
//  Function()
//  : _function(NULL)
//  , _signature(NULL) {}
//
//  Function(const Function &o)
//  {
//	  _function = o._function;
//	  _signature = o._signature;
//  }
//
//  template<typename Lambda>
//  Function(Lambda &&lambda) {
//    auto function = new decltype(makeFunction(lambda))(makeFunction(lambda));
//    _function  = static_cast<void*>(function);
//    _signature = &typeid(function);
//  }
//
//  template<typename ...Args>
//  void operator()(Args ...args) {
//    auto function = static_cast<std::function<void(Args...)>*>(
//      _function);
//    if (typeid(function) != *(_signature))
//      throw std::bad_cast();
//    (*function)(args...);
//  }
//
//  void clear() {
//    if (_function)
//      delete static_cast<std::function<void()>*>(_function);
//    _function = NULL;
//    _signature = NULL;
//  }
//
//private:
//
//  void *_function;
//  std::type_info const *_signature;
//
//};
//
//class EventDispatcher {
//  public:
//    EventDispatcher() {}
//	EventDispatcher(const EventDispatcher &o)
//	{
//		_listeners = o._listeners;
//	}
//
//    ~EventDispatcher () {
//      for (auto listener : _listeners)
//        listener.second.clear();
//    }
//
//    template <typename Lambda>
//    void on(std::string const &name, Lambda &&lambda) {
//      _listeners[name] = lambda;
//    }
//
//    void off (std::string const &name) {
//      if (_listeners.find(name) == _listeners.end())
//        return;
//      _listeners[name].clear();
//    }
//
//    template <typename ...Args>
//    void trigger(std::string const &name, Args ...args) {
//      if (_listeners.find(name) != _listeners.end())
//        _listeners[name](args...);
//    }
//
//  private:
//    std::unordered_map<std::string, Function> _listeners;
//};
//
//int
//main (int argc, char* argv[])
//{
//
//  Function func = [] (int a) {
//    std::cout << "Hello " << a << std::endl;
//  };
//
//  Function func2 = [] () {
//    std::cout << "world" << std::endl;
//  };
//
//  func(42);
//  func2();
//
//  func.clear();
//  func2.clear();
//
//
//  // Test events
//  EventDispatcher test;
//
//  test.on("event", [](int a, float b, char const *lol) {
//    std::cout << "a: " << a << std::endl;
//    std::cout << "b: " << b << std::endl;
//    std::cout << "lol: " << lol << std::endl;
//  });
//
//  test.trigger("event", 23, 5.4f, "lol");
//  test.trigger("event", 23, 43.4f, "banane");
//
//  EventDispatcher loader;
//
//  loader.on("progress", [] (float progress) {
//    std::cout << "Progress = " << progress << std::endl;
//  });
//
//  loader.on("finish", [] () {
//    std::cout << "Finished !" << std::endl;
//  });
//
//  EventDispatcher loader2(loader);
//
//  loader2.trigger("progress", 0.1f);
//  loader2.trigger("finish");
//
//  return 0;
//}