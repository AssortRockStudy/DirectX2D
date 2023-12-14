#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
    : m_hRenderWnd(nullptr)
{

}

CDevice::~CDevice()
{

}

int CDevice::init(HWND _hWnd, Vec2 _vResolution)
{
    m_hRenderWnd = _hWnd;
    m_vRenderResolution = _vResolution;

    // --------------------------
    // (1) Device & DeviceContext ����
	// --------------------------
    // device initialize
    D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL_11_0;
    if (FAILED( D3D11CreateDevice(nullptr
        , D3D_DRIVER_TYPE_HARDWARE, nullptr
        , D3D11_CREATE_DEVICE_DEBUG
        , nullptr, 0, D3D11_SDK_VERSION
        , m_Device.GetAddressOf(), &eLevel, m_Context.GetAddressOf()) ))
    {
        MessageBox(nullptr, L"Fail to Create Device", L"Fail to Initialize", MB_OK);
        return E_FAIL;
    }

    // --------------------------
    // (2) SwapChain ����
    // --------------------------
    // create swapChain
    if (FAILED(CreateSwapChain()))
    {
        MessageBox(nullptr, L"Fail to Create SwapChain", L"Fail to Initialize", MB_OK);
        return E_FAIL;
    }

    // --------------------------
    // (3) TargetView ���� (DepthStencil & View)
    // --------------------------
    // (4) OM ����
    // --------------------------
    // create render target, render target view, depth stencil, depth stencil view
    if (FAILED(CreateTargetView()))
    {
        MessageBox(nullptr, L"Fail to Create Target&View", L"Fail to Initialize", MB_OK);
        return E_FAIL;
    }

    // --------------------------
    // (5) Viewport setting
    // --------------------------
    D3D11_VIEWPORT ViewportDesc = {};

    ViewportDesc.MaxDepth = 0;
    ViewportDesc.MaxDepth = 1.f;
    ViewportDesc.TopLeftX = 0;
    ViewportDesc.TopLeftY = 0;
    ViewportDesc.Width = m_vRenderResolution.x;
    ViewportDesc.Height = m_vRenderResolution.y;

    CONTEXT->RSSetViewports(1, &ViewportDesc);

    return S_OK;
}

void CDevice::ClearRenderTarget(float(&Color)[4])
{
    // RenderTargetTexture ���� �ʱ�ȭ
    // - Color: Normalized Value (0~255 X , 0~1 O)
    // - Depth: 0~1, 1�� ������ �־���
    m_Context->ClearRenderTargetView(m_RTView.Get(), Color);
    m_Context->ClearDepthStencilView(m_DSView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
    // Present() Buffer �׸�
    m_SwapChain->Present(0, 0);
}

int CDevice::CreateSwapChain()
{
    // SwapChain ���� ����ü
    // - SwapChain�� �����ϴ� Render Target Buffer�� ���� ����
    DXGI_SWAP_CHAIN_DESC tDesc = {};
    tDesc.BufferCount = 1; // ������ ���۴� �ϳ�
    tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    tDesc.BufferDesc.Width = (UINT)m_vRenderResolution.x;
    tDesc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
    tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32bit
    tDesc.BufferDesc.RefreshRate.Denominator = 1;
    tDesc.BufferDesc.RefreshRate.Numerator = 60;
    tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    tDesc.Flags = 0;
    tDesc.SampleDesc.Count = 1;
    tDesc.SampleDesc.Quality = 0;
    tDesc.Windowed = true; // â���
    tDesc.OutputWindow = m_hRenderWnd;

    // Access Factor 
    // - Factory: swapChain ���� ���
    // - SwapChain ���� ����: Device -> Adapter -> Factory -> Swapchain
    ComPtr<IDXGIDevice> pldxgiDevice = nullptr;
    ComPtr<IDXGIAdapter> pAdapter = nullptr;
    ComPtr<IDXGIFactory> pFactory = nullptr;
    m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pldxgiDevice.GetAddressOf());
    pldxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
    pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

    // Create SwapChain
    if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf())))
    {
        return E_FAIL;
    }

    return S_OK;
}

int CDevice::CreateTargetView()
{
    // Get Render Target Texture & View
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());
    m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTView.GetAddressOf());

    // Create Depth Stencil Texture
    D3D11_TEXTURE2D_DESC Desc = {};
    Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;// depth 24bit + stencil 8bit
    Desc.Width = (UINT)m_vRenderResolution.x;   // depth stencil state texture �ػ󵵴� renter target texture �ػ󵵿� ���ƾ� ��
    Desc.Height = (UINT)m_vRenderResolution.y;
    Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;  // �뵵
    Desc.CPUAccessFlags = 0;                    // CPU ���� �Ұ�
    Desc.Usage = D3D11_USAGE_DEFAULT;
    Desc.SampleDesc.Count = 1;                  // sampling
    Desc.SampleDesc.Quality = 0;
    Desc.MipLevels = 1;                         // ������Ƽ ���� �纻 ��������
    Desc.MiscFlags = 0;
    Desc.ArraySize = 1;

    if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DSTex.GetAddressOf())))
        return E_FAIL;

    // Get Depth Stencil View
    m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSView.GetAddressOf());

    // Output Merge State(OM)�� Render Target Texture�� Depth Stencil Texture ����
    m_Context->OMSetRenderTargets(1, m_RTView.GetAddressOf(), m_DSView.Get());

    return S_OK;
}
