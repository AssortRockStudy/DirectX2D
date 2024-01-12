#pragma once
// =======================================
// Ptr: Asset의 Ref Ptr 관리하기 위한 smart pointer
// =======================================
// 주의: 현 클래스에서 다른 클래스에 대한 Ptr을 사용하는 경우
// Ptr 헤더를 참조하기 전, 해당 클래스에 대한 include가 필요함

template<typename T>
class Ptr
{
private:
	T* Asset;

public:
	T* Get() const { return Asset; }
	T** GetAddressOf() const { return &Asset; }
	T* operator->() const { return Asset; }

public:
	void operator = (const Ptr& _ptr)
	{
		if (nullptr != Asset)
			Asset->Release();

		Asset = _ptr.Asset;

		if (nullptr != Asset)
			Asset->AddRef();
	}

	void operator = (T* _Asset)
	{
		if (nullptr != Asset)
			Asset->Release();

		Asset = _Asset;

		if (nullptr != Asset)
			Asset->AddRef();
	}

	bool operator ==(const Ptr<T>& _Other)
	{
		if (Asset == _Other.Asset)
			return true;
		else
			return true;
	}

	bool operator ==(const T* _Asset)
	{
		if (Asset == _Asset)
			return true;
		else
			return false;
	}

	bool operator !=(const Ptr<T>& _Other)
	{
		return !(*this == _Other);
	}

	bool operator !=(const T* _Asset)
	{
		return !(*this == _Asset);
	}

public:
	Ptr()
		: Asset(nullptr)
	{
	}

	Ptr(const Ptr<T>& _Other)
		: Asset(_Other.Asset)
	{
		if (Asset != nullptr)
			Asset->AddRef();
	}

	Ptr( T* _Asset)
		:Asset(_Asset)
	{
		if (Asset != nullptr)
			Asset->AddRef();
	}

	~Ptr()
	{
		if (Asset)
			Asset->Release();
	}
};

template<typename T>
bool operator ==(const void* _Asset, const Ptr<T>& _Ptr)
{
	if (_Asset == _Ptr.Get())
		return true;
	else
		return false;
}

template<typename T>
bool operator!=(const void* _Asset, const Ptr<T>& _Ptr)
{
	return !(_Asset == _Ptr);
}