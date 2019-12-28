#pragma once
#include <iostream>

template<typename T> class Singleton
{
public:
	static T* Instance()
	{
		if (_instance == NULL)
			_instance = new T;

		_ASSERT(_instance != NULL);

		return _instance;
	};
protected:
	static T* _instance;
	Singleton();
};


template<typename T> T* Singleton<T>::_instance = NULL;

template<typename T>
inline Singleton<T>::Singleton()
{
}