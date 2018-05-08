#ifndef SINGLETONT_H_
#define SINGLETONT_H_
//
#include "boost/noncopyable.hpp"
#include "boost/thread.hpp"


template<typename T> class CSingletonT : boost::noncopyable
{
	//
public:
	//
	static T* instance()
	{
		boost::call_once(&init, once_);
		return value_;
	}

private:
	//
	static void init()
	{
        delete value_;
        value_ = 0;
		value_ = new T();
	}

private:
	//
	static boost::once_flag once_;
	static T* value_;
};
//
template<typename T> boost::once_flag CSingletonT<T>::once_ = BOOST_ONCE_INIT;
//
template<typename T> T* CSingletonT<T>::value_;
//
#endif
//

