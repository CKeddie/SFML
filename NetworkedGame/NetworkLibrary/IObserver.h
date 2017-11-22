#pragma once

template <class T>
class IObserver
{
public:
	virtual void OnNotify(T) = 0;
};

