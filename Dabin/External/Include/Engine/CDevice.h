#pragma once

// =======================================
// CDevice: DRX11 Graphic Device
// =======================================

class CDevice :
    public CSingleton<CDevice>
{
    SINGLE(CDevice);

private:
    ComPtr<ID3D11Device>            m_Device;       // GPU �޸� ���� & ��ü ����
    ComPtr<ID3D11DeviceContext>     m_Context;      // GPU ������ ���
    ComPtr<IDXGISwapChain>          m_SwapChain;    // ��� ���� ����

    // OM (Ouput Merge State)
    ComPtr<ID3D11Texture2D>         m_RTTex;        // Render Target
    ComPtr<ID3D11RenderTargetView>  m_RTView;
    ComPtr<ID3D11Texture2D>         m_DSTex;        // Depth Stencil
    ComPtr<ID3D11DepthStencilView>  m_DSView;
    HWND                            m_hRenderWnd;
    Vec2                            m_vRenderResolution;

public:
    int init(HWND _hWnd, Vec2 _vResolution);
    void ClearRenderTarget(float(&Color)[4]);
    void Present();
    ID3D11Device* GetDevice() { return m_Device.Get(); }
    ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

private:
    int CreateSwapChain();
    int CreateTargetView();
};