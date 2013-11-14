#ifndef   __PUBLISHER_HPP__
# define  __PUBLISHER_HPP__

#include <vector>
#include <algorithm>

#include "Any.hpp"

struct Subscriber
{};

struct Emitter
{};



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



#endif    //__PUBLISHER_HPP__