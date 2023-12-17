#pragma once
//class SmartPointer
//{
//	int* pInt;
//
//public:
//	int* Get()
//	{
//		return pInt;
//	}
//
//	int** GetAdressOf()
//	{
//		return &pInt;
//	}
//};

class CConstBuffer;

class CDevice : public CSingleton<CDevice>
{
	SINGLETON(CDevice);

private:

	HWND							m_hRenderWnd;
	Vec2							m_vRenderResolution;


	ComPtr<ID3D11Device>								m_Device;	// GPU 메모리 관리, 객체 생성
	ComPtr<ID3D11DeviceContext>				m_Context;	// GPU 렌더링 명령 

	ComPtr<IDXGISwapChain>							m_SwapChain; // 스왚체인(출력 버퍼 지정)

	// OM(OutputMergeState)
	ComPtr<ID3D11Texture2D>						m_RTTex;     // 렌더타겟 텍스쳐
	ComPtr<ID3D11RenderTargetView>		m_RTView;    // 렌더타겟 뷰

	ComPtr<ID3D11Texture2D>						m_DSTex;	 // 뎊스 스텐실 텍스쳐	
	ComPtr<ID3D11DepthStencilView>			m_DSView;	// 뎊스 스텐실 뷰

	CConstBuffer* m_arrCB[(UINT)CB_TYPE::END];
private:
	int CreateSwapChain();
	int CreateTargetView();
	int CreateConstBuffer();

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
	void Present();

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }
	CConstBuffer* GetConstBuffer(CB_TYPE _type) { return m_arrCB[(UINT)_type]; }

};

