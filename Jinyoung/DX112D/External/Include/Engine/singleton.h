#pragma once


template<typename T>
class CSingleton
{
private:
	static T* m_This;

public:
	static T* GetInst()
	{
		if (nullptr == m_This)
		{
			m_This = new T;
		}

		return m_This;
	}

	static void Destroy()
	{
		if (nullptr != m_This)
		{
			delete m_This;
			m_This = nullptr;
		}
	}

public:
	CSingleton()
	{
		typedef void(*FUNC_TYPE)(void);
		//메인함수가 종료될때 실행되는 함수를 등록
		atexit((FUNC_TYPE)(&CSingleton::Destroy));
	}
	~CSingleton()
	{

	}
};

template<typename T>
T* CSingleton<T>::m_This = nullptr;