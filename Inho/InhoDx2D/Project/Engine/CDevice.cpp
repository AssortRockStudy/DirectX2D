#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
    : m_hRenderWnd(nullptr)
{

}

CDevice::~CDevice()
{}


int CDevice::init(HWND _hWnd, Vec2 _vResolution)
{
    // ��� ������
    m_hRenderWnd = _hWnd;

    // ���� �ػ�
    m_vRenderResolution = _vResolution;

    // ��ġ �ʱ�ȭ
    D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL_11_0;

    if (FAILED(D3D11CreateDevice(nullptr 
        , D3D_DRIVER_TYPE_HARDWARE, nullptr
        , D3D11_CREATE_DEVICE_DEBUG
        , nullptr
        , 0
        , D3D11_SDK_VERSION
        , m_Device.GetAddressOf(), &eLevel, m_Context.GetAddressOf()))) {

        MessageBox(nullptr, L"Device, Context ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain())) {
        MessageBox(nullptr, L"SwapChain ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateTargetView())) {
        MessageBox(nullptr, L"Ÿ�� �� View ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
        return E_FAIL;
    }






    return S_OK;
}

int CDevice::CreateSwapChain()
{
    // ����ü�� ���� ����ü
    DXGI_SWAP_CHAIN_DESC tDesc = {};

    // ����ü���� �����ϴ� ����(����Ÿ��)�� ���� ����
    tDesc.BufferCount = 1;
    tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    tDesc.BufferDesc.Width = (UINT)m_vRenderResolution.x;
    tDesc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
    tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tDesc.BufferDesc.RefreshRate.Denominator = 1;
    tDesc.BufferDesc.RefreshRate.Numerator = 60;
    tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    tDesc.Flags = 0;

    tDesc.SampleDesc.Count = 1;
    tDesc.SampleDesc.Quality = 0;

    tDesc.Windowed = true; // â���
    tDesc.OutputWindow = m_hRenderWnd; // ���� ü���� ��� ������

    ComPtr<IDXGIDevice> pIdxgiDevice = nullptr;
    ComPtr<IDXGIAdapter> pAdapter = nullptr;
    ComPtr<IDXGIFactory> pFactory = nullptr;

    m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pIdxgiDevice.GetAddressOf());
    pIdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
    pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

    if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf()))) {
        return E_FAIL;
    }

    return S_OK;

}

int CDevice::CreateTargetView()
{
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());

    m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTView.GetAddressOf());

    D3D11_TEXTURE2D_DESC Desc = {};

    Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    Desc.Width = (UINT)m_vRenderResolution.x;
    Desc.Height = (UINT)m_vRenderResolution.y;

    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;

    Desc.MipLevels = 1;
    Desc.MiscFlags = 0;

    Desc.ArraySize = 1;

    if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DSTex.GetAddressOf()))) {
        return E_FAIL;
    }

    m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSView.GetAddressOf());

    m_Context->OMSetRenderTargets(1, m_RTView.GetAddressOf(), m_DSView.Get());

    return 0;
}
