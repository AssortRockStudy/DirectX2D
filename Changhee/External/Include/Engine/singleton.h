#pragma once


template<typename T>
class CSingleton
{
private:
	static T* m_pThis;

public:
	static T* GetInst()
	{
		if (nullptr == m_pThis)
		{
			m_pThis = new T;
		}

		return m_pThis;
	}

	static void Destroy()
	{
		if (nullptr != m_pThis)
		{
			delete m_pThis;
			m_pThis = nullptr;
		}
	}


public:
	CSingleton()
	{
		typedef void(*FUNC_TYPE)(void);
		atexit((FUNC_TYPE)(&CSingleton::Destroy));
	}
	~CSingleton()
	{

	}

};

template<typename T>
T* CSingleton<T>::m_pThis = nullptr;