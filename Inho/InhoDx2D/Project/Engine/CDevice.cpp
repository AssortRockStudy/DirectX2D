#include "pch.h"
#include "CDevice.h"

#include "CConstBuffer.h"

CDevice::CDevice()
    : m_hRenderWnd(nullptr)
    , m_arrCB{}
    , m_arrRS{}
    , m_arrDS{}
    , m_arrBS{}
{

}

CDevice::~CDevice()
{
    Delete_Array(m_arrCB);
}


int CDevice::init(HWND _hWnd, Vec2 _vResolution)
{
    // 출력 윈도우
    m_hRenderWnd = _hWnd;

    // 버퍼 해상도
    m_vRenderResolution = _vResolution;

    // 장치 초기화
    D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL_11_0;

    if (FAILED(D3D11CreateDevice(nullptr 
        , D3D_DRIVER_TYPE_HARDWARE, nullptr
        , D3D11_CREATE_DEVICE_DEBUG
        , nullptr
        , 0
        , D3D11_SDK_VERSION
        , m_Device.GetAddressOf(), &eLevel, m_Context.GetAddressOf()))) {

        MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain())) {
        MessageBox(nullptr, L"SwapChain 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateTargetView())) {
        MessageBox(nullptr, L"타겟 및 View 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateRasterizerState())) {
        MessageBox(nullptr, L"Rasterizer State 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateDepthStencilState())) {
        MessageBox(nullptr, L"DepthStencil State 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }

    if (FAILED(CreateBlendState())) {
        MessageBox(nullptr, L"Blend State 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }

    // 뷰포트 설정
    D3D11_VIEWPORT ViewportDesc = {};

    ViewportDesc.MinDepth = 0;
    ViewportDesc.MaxDepth = 1.f;

    ViewportDesc.TopLeftX = 0;
    ViewportDesc.TopLeftY = 0;
    ViewportDesc.Width = m_vRenderResolution.x;
    ViewportDesc.Height = m_vRenderResolution.y;

    CONTEXT->RSSetViewports(1, &ViewportDesc);

    if (FAILED(CreateConstBuffer())) {
        MessageBox(nullptr, L"상수버퍼 생성 실패", L"Device 초기화 실패", MB_OK);
        return E_FAIL;
    }


    return S_OK;
}

void CDevice::ClearRenderTarget(float(&Color)[4])
{
    m_Context->ClearRenderTargetView(m_RTView.Get(), Color);
    m_Context->ClearDepthStencilView(m_DSView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
    m_SwapChain->Present(0, 0);
}

int CDevice::CreateSwapChain()
{
    // 스왑체인 생성 구조체
    DXGI_SWAP_CHAIN_DESC tDesc = {};

    // 스왑체인이 관리하는 버퍼(렌더타겟)의 구성 정보
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

    tDesc.Windowed = true; // 창모드
    tDesc.OutputWindow = m_hRenderWnd; // 스왑 체인의 출력 윈도우

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

    // DepthStencil 용도의 텍스처
    Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    // CPU 접근 불가
    Desc.CPUAccessFlags = 0;
    Desc.Usage = D3D11_USAGE_DEFAULT;

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

    return S_OK;
}

int CDevice::CreateRasterizerState()
{
    m_arrRS[(UINT)RS_TYPE::CULL_BACK] = nullptr;

    HRESULT result = S_OK;

    D3D11_RASTERIZER_DESC tDesc = {};

    tDesc.CullMode = D3D11_CULL_FRONT;
    tDesc.FillMode = D3D11_FILL_SOLID;
    result = DEVICE->CreateRasterizerState(&tDesc, m_arrRS[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());
    if (FAILED(result))
        return E_FAIL;

    tDesc.CullMode = D3D11_CULL_NONE;
    tDesc.FillMode = D3D11_FILL_SOLID;
    result = DEVICE->CreateRasterizerState(&tDesc, m_arrRS[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());
    if (FAILED(result))
        return E_FAIL;

    tDesc.CullMode = D3D11_CULL_NONE;
    tDesc.FillMode = D3D11_FILL_WIREFRAME;
    result = DEVICE->CreateRasterizerState(&tDesc, m_arrRS[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());
    if (FAILED(result))
        return E_FAIL;

    return S_OK;
}

int CDevice::CreateDepthStencilState()
{
    HRESULT hr = S_OK;

    m_arrDS[(UINT)DS_TYPE::LESS] = nullptr;

    D3D11_DEPTH_STENCIL_DESC tDesc = {};

    tDesc.DepthEnable = true;
    tDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    tDesc.StencilEnable = false;
    hr = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf());
    if (FAILED(hr)) return E_FAIL;

    tDesc.DepthEnable = true;
    tDesc.DepthFunc = D3D11_COMPARISON_GREATER;
    tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    tDesc.StencilEnable = false;
    hr = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::GREATER].GetAddressOf());
    if (FAILED(hr)) return E_FAIL;

    tDesc.DepthEnable = true;
    tDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
    tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    tDesc.StencilEnable = false;
    hr = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::GREATER_EQUAL].GetAddressOf());
    if (FAILED(hr)) return E_FAIL;

    tDesc.DepthEnable = false;
    tDesc.DepthFunc = D3D11_COMPARISON_NEVER;
    tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    tDesc.StencilEnable = false;
    hr = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::NO_TEST].GetAddressOf());
    if (FAILED(hr)) return E_FAIL;

    tDesc.DepthEnable = true;
    tDesc.DepthFunc = D3D11_COMPARISON_LESS;
    tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    tDesc.StencilEnable = false;
    hr = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::NO_WRITE].GetAddressOf());
    if (FAILED(hr)) return E_FAIL;

    tDesc.DepthEnable = false;
    tDesc.DepthFunc = D3D11_COMPARISON_NEVER;
    tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    tDesc.StencilEnable = false;
    hr = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());
    if (FAILED(hr)) return E_FAIL;

    return S_OK;
}

int CDevice::CreateBlendState()
{
    m_arrBS[(UINT)BS_TYPE::DEFAULT] = nullptr;

    D3D11_BLEND_DESC tDesc = {};

    tDesc.AlphaToCoverageEnable = false;
    tDesc.IndependentBlendEnable = true;

    tDesc.RenderTarget[0].BlendEnable = true;
    tDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    tDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    tDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

    tDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    tDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    tDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

    tDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    DEVICE->CreateBlendState(&tDesc, m_arrBS[(UINT)BS_TYPE::ALPHA_BLEND].GetAddressOf());

    return S_OK;
}

int CDevice::CreateConstBuffer()
{
    m_arrCB[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer;
    m_arrCB[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform), 1);
    return 0;
}
