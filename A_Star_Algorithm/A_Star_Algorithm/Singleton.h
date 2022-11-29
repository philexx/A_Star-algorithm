#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class tSingleton
{
protected:
	static T* singleton;
public:
	static T* Get()
	{
		if (!singleton)
		{
			singleton = new T;
		}
		return singleton;
	}

	void Delete() const
	{
		if (singleton)
		{
			delete singleton;
			singleton = nullptr;
		}
	}

};

template <class T>
T* tSingleton<T>::singleton = 0;
#endif // !SINGLETON_H
