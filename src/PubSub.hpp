#ifndef   __PUBLISHER_HPP__
# define  __PUBLISHER_HPP__

#include <algorithm>
#include <unordered_set>
#include <map>

#include "Any.hpp"

template <typename F>
struct MyFunc : public MyFunc<decltype(&F::operator())>
{};

template <typename Type, typename Return, typename... Args>
struct MyFunc<Return(Type::*)(Args...) const>
{
	typedef Return(*pointer)(Args...);
	typedef std::function<Return(Args...)> function;
};

template <typename F>
typename MyFunc<F>::pointer
toFnPointer(F &lambda)
{
	return static_cast<typename MyFunc<F>::pointer>(lambda);
}


template <typename F>
typename MyFunc<F>::function
toFn(F &lambda)
{
	return static_cast<typename MyFunc<F>::function>(lambda);
}

class PubSub
{
private:
	struct Callback
	{
		void *function;
		const std::type_info *signature;
	};
public:
	void clearAll()
	{
		for (auto &e : _allCallbacks)
		{
			delete static_cast<std::function<void()>*>(e.second.function);
		}
	}

	void clear()
	{
		for (auto &e : _callbacks)
		{
			delete static_cast<std::function<void()>*>(e.second.function);
		}
	}

	template <typename F>
	void sub(const std::string &key, F lambda)
	{
		if (_callbacks.find(key) != std::end(_callbacks))
			return;
		auto fn = new decltype(toFn(lambda))(toFn(lambda));
		_callbacks[key].function = static_cast<void*>(fn);
		_callbacks[key].signature = &typeid(fn);
	}

	void unsub(const std::string &key)
	{
		if (_callbacks.find(key) == std::end(_callbacks))
			return;
		delete static_cast<std::function<void()>*>(_callbacks[key].function);
	}

	template <typename ...Args>
	void pub(std::string name, Args ...args)
	{
		auto callback = _callbacks.at(name);
		auto function = static_cast<std::function<void(Args...)>*>(callback.function);

		if (typeid(function) != *(callback.signature))
		{
			std::cerr << "PubSub error : Wrong pub call." << std::endl;
			return;
		}
		(*function)(args...);
	}
	PubSub(){}
	virtual ~PubSub()
	{
		clear();
	}
private:
	std::map<std::string, Callback> _callbacks;
	static std::multimap<std::string, Callback> _allCallbacks;
};

#endif    //__PUBLISHER_HPP__