#pragma once

// =======================================
// CDevice: DRX11 Graphic Device
// =======================================

class CDevice :
    public CSingleton<CDevice>
{
    SINGLE(CDevice);

private:
    ComPtr<ID3D11Device>            m_Device;       // GPU 메모리 관리 & 객체 생성
    ComPtr<ID3D11DeviceContext>     m_Context;      // GPU 렌더링 명령
    ComPtr<IDXGISwapChain>          m_SwapChain;    // 출력 버퍼 지정

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