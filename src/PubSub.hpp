#ifndef   __PUBLISHER_HPP__
# define  __PUBLISHER_HPP__

#include <algorithm>
#include <unordered_set>

#include "Any.hpp"
#include "Singleton.hpp"

class PubSub : public Singleton<PubSub>
{
public:
	void subscribe(std::shared_ptr<Any> obj, const std::string &key)
	{
		auto &set = _list.find(key);
		if (set == std::end(_list))
		{
			_list.insert(std::make_pair(key, std::unordered_set<std::shared_ptr<Any> >()));
			set = _list.find(key);
		}
		set->second.insert(obj);
	}

	void unsubscribe(std::shared_ptr<Any> obj, const std::string &key)
	{
		auto &set = _list.find(key);
		if (set == std::end(_list))
			return;
		set->second.erase(obj);
	}

	template <typename ...Types>
	void publish(const std::string &s, Types... types)
	{
		auto &set = _list.find(s);
		if (set == std::end(_list))
			return;
		for (auto &e : set->second)
		{
			auto fun = e.get<std::function<void(Types...)> >();
			fun(types...);
		}
	}

private:
	std::map<std::string, std::unordered_set<std::shared_ptr<Any> > > _list;
	friend class Singleton<PubSub>;
};


std::map<std::string, Any> database;

struct Subscriber
{
	template <typename T>
	void subscribe(const std::string &s, T &callback)
	{		
		database.insert(std::make_pair(s, Any(callback)));
	}
};

struct Emitter
{
	template <typename ...Types>
	void emit(const std::string &s, Types... types)
	{
		auto &f = database.find(s);
		if (f == std::end(database))
			return;
		auto fun = f->second.get<std::function<void(Types...)> >();
		fun(types...);
	}
};

#endif    //__PUBLISHER_HPP__