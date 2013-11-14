#ifndef   __PUBLISHER_HPP__
# define  __PUBLISHER_HPP__

#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

//namespace PubSub
//{
//	using Registration = std::shared_ptr<void>;
//
//	using UniversalPtr = std::shared_ptr<void>;
//
//	template <typename Deleter>
//	UniversalPtr createEmptyPtr(Deleter deleter)
//	{
//		return UniversalPtr((void*)0xDEADC0DE, deleter);
//	}
//
//	UniversalPtr createHeartBeat()
//	{
//		return createEmptyPtr([] (void*) {});
//	}
//
//	class SubjectBase
//	{
//	protected:
//		SubjectBase()
//			: _heartBeat(createHeartBeat())
//		{}
//
//		Registration registerObserver(UniversalPtr ptr)
//		{
//			_observers.push_back(ptr);
//			std::weak_ptr<UniversalPtr::element_type> weakHeartBeat(_heartBeat);
//
//			return createEmptyPtr([ptr, weakHeartBeat, this](void*)
//			{
//				_observers.erase(std::remove(std::begin(_observers), std::end(_observers), ptr), std::end(_observers));
//			});
//		}
//
//	protected:
//		std::vector<UniversalPtr> _observers;
//	private:
//		UniversalPtr _heartBeat;
//	};
//
//	template <typename Signature>
//	struct Subject;
//
//	template <typename Return, typename... Params>
//	struct Subject<Return (Params...)>
//		: SubjectBase
//	{
//		using F = std::function<Return (Params...)>;
//		using FPtr = std::shared_ptr<F>;
//
//		void operator()(Params... params)			
//		{
//			for (const auto &o : _observers)
//			{
//				const FPtr fptr = std::static_pointer_cast<F>(o);
//				(*fptr)(params...);
//			}
//		}
//
//		Registration registerObserver(F f)
//		{
//			FPtr fptr(new F(std::move(f)));
//			return SubjectBase::registerObserver(fptr);
//		}
//	};
//};

struct IData
{
};

template <typename T>
struct Data : public IData
{
	T data;

	Data(T d)
		: data(d)
	{}

	virtual ~Data()
	{}

	T get()
	{
		return data;
	}

	T& operator=(T &d)
	{
		data = d;
		return d;
	}
};

class Any
{
private:
	IData *_data;
public:
	template<typename T>
	Any(T d)
		: _data(new Data<T>(d))
	{}

	~Any()
	{}

	template<typename T>
	T get()
	{
		return static_cast<T>(_data).get();
	}

	template<typename T>
	operator T() const
	{
		return (static_cast<Data<T>* >(_data))->get();
	}
};

#endif    //__PUBLISHER_HPP__