#pragma once

class CConstBuffer;
class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice);
private:
	ComPtr<ID3D11Device> m_Device; // GPU ¸Þ¸ð¸® °ü¸®, °´Ã¼ »ý¼º
	ComPtr<ID3D11DeviceContext> m_Context; // GPU ·»´õ¸µ ¸í·É

	ComPtr<IDXGISwapChain> m_SwapChain; // ½º¿ÒÃ¼ÀÎ( Ãâ·Â ¹öÆÛ ÁöÁ¤ )

	// OM(OutputMergeState)
	ComPtr<ID3D11Texture2D> m_RTTex; // ·»´õ Å¸°Ù ÅØ½ºÃÄ
	ComPtr<ID3D11RenderTargetView> m_RTView; // ·»´õ Å¸°Ù ºä

	ComPtr<ID3D11Texture2D> m_DSTex; // µª½º ½ºÅÙ½Ç ÅØ½ºÃÄ
	ComPtr<ID3D11DepthStencilView> m_DSView; // µª½º ½ºÅÙ½Ç ºä

	HWND  m_hRenderWnd;
	Vec2 m_vRenderResolution;

	
	CConstBuffer* m_arrCB[(UINT)CB_TYPE::END];

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
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

