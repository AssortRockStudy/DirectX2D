#pragma once

class CConstBuffer;

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice);

private:
	HWND							m_hRenderWnd;
	Vec2							m_vRenderResolution;

	ComPtr<ID3D11Device>			m_Device;			// GPU �޸� ����, ��ü ����
	ComPtr<ID3D11DeviceContext>		m_Context;			// GPU ������ ����

	ComPtr<IDXGISwapChain>			m_SwapChain;		// SwapChain(��� ���� ����)

	//OM(OutputMergeState)
	ComPtr<ID3D11Texture2D>			m_RTTex;			// ����Ÿ�� �ؽ���
	ComPtr<ID3D11RenderTargetView>	m_RTView;			// ����Ÿ�� ��

	ComPtr<ID3D11Texture2D>			m_DSTex;			// �X�� ���ٽ� �ؽ���
	ComPtr<ID3D11DepthStencilView>	m_DSView;			// �X�� ���ٽ� ��

	CConstBuffer*					m_arrCB[(UINT)CB_TYPE::END];

	ComPtr<ID3D11RasterizerState>	m_arrRS[(UINT)RS_TYPE::END];
	ComPtr<ID3D11DepthStencilState>	m_arrDS[(UINT)DS_TYPE::END];
	ComPtr<ID3D11BlendState>		m_arrBS[(UINT)BS_TYPE::END];

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
	void Present();

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	CConstBuffer* GetConstBuffer(CB_TYPE _type) { return m_arrCB[(UINT)_type]; }
	Vec2 GetRenderResolution() { return m_vRenderResolution; }

	ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_arrRS[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_arrDS[(UINT)_Type]; }
	ComPtr<ID3D11BlendState> GetBSState(BS_TYPE _Type) { return m_arrBS[(UINT)_Type]; }

private:
	int CreateSwapChain();
	int CreateTargetView();
	int CreateRasterizerState();
	int CreateDepthStencilState();
	int CreateBlendState();

	int CreateConstBuffer();

};

