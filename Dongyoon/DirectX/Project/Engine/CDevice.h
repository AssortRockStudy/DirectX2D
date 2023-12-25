#pragma once

template<typename T>
class MyPtr
{
private:
	T* m_Target;

public:
	~MyPtr()
	{
		m_Target->Release();
	}
};

class SmartPointer
{
	int* pInt;

public:
	int* get()
	{
		return pInt;
	}

	int** GetAdressOf()
	{
		return &pInt;
	}
};

class CConstBuffer;

//Directx11 ���� GPU ���� 
class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice);

private:
	ComPtr<ID3D11Device>				m_Device;		//GPU �޸�  ����, ��ü ����
	ComPtr<ID3D11DeviceContext>			m_Context;		// GPU ������ ���

	ComPtr<IDXGISwapChain>				m_SwapChain;	//����ü��(��� ���� ����)

	ComPtr<ID3D11Texture2D>				m_RTTex;		// ����Ÿ�� �ؽ���
	ComPtr<ID3D11RenderTargetView>		m_RTView;		//���� Ÿ�� ��

	ComPtr<ID3D11Texture2D>				m_DSTex;		// ���� ���ٽ� �ؽ���
	ComPtr<ID3D11DepthStencilView>		m_DSView;		// ���� ���ٽ� ��

	HWND								m_hRenderWnd;
	Vec2								m_vRenderResolution;

	CConstBuffer*						m_arrCB[(UINT)CB_TYPE::END];


public:
	int Init(HWND _hwnd, Vec2 _vResolution);

	void ClearRenderTarget(float(&color)[4]);
	void Present();

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	CConstBuffer* GetConstBuffer(CB_TYPE _type) { return m_arrCB[(UINT)_type]; }

	Vec2 GetRenderResolution() { return m_vRenderResolution; }


private:
	int CreateSwapChain();
	int CreateTargetView();
	int CreateConstBuffer();
};

