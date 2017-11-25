#pragma once

#include "IObserver.h"
#include <vector>

template<class T>
class ISubject
{
public:
	virtual void Attach(IObserver<T> * observer);
	virtual void Notify(T data);
private:
	std::vector<IObserver<T>*> _observers;
};

template<class T>
inline void ISubject<T>::Attach(IObserver<T>* observer)
{
	_observers.push_back(observer);
}

template<class T>
inline void ISubject<T>::Notify(T data)
{
	for (unsigned int i = 0; i < _observers.size(); i++)
	{
		_observers[i]->OnNotify(data);
	}
}