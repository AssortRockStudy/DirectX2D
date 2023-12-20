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
								, nullptr, 0, D3D11_SDK_VERSION
								, m_Device.GetAddressOf(), &eLevel, m_Context.GetAddressOf())))
	{
		MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// SwapChain 생성
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 렌더타겟, 렌더타겟 뷰, 뎁스스텐실 타겟, 뎁스 스텐실 뷰 생성
	if (FAILED(CreateTargetView()))
	{
		MessageBox(nullptr, L"타겟 및 View 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateRasterizerState()))
	{
		MessageBox(nullptr, L"RasterizerState 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateDepthStencilState()))
	{
		MessageBox(nullptr, L"DepthStencilState 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(CreateBlendState()))
	{
		MessageBox(nullptr, L"BlendState 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// ViewPort 설정
	D3D11_VIEWPORT ViewportDesc = {};

	ViewportDesc.MinDepth = 0;
	ViewportDesc.MaxDepth = 1.f;

	ViewportDesc.TopLeftX = 0;
	ViewportDesc.TopLeftY = 0;
	ViewportDesc.Width = m_vRenderResolution.x;
	ViewportDesc.Height = m_vRenderResolution.y;

	CONTEXT->RSSetViewports(1, &ViewportDesc);

	if (FAILED(CreateConstBuffer()))
	{
		MessageBox(nullptr, L"상수 버퍼 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateSwapChain()
{
	// SwapChain 생성 구조체
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	// SwapChain 이 관리하는 Buffer(RenderTarget) 의 구성 정보
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

	// 창모드
	tDesc.Windowed = true;
	
	// SwapChain의 출력 윈도우 지정
	tDesc.OutputWindow = m_hRenderWnd;


	// SwapChain 생성기능을 가지고 있는 Factory 에 접근한다.
	ComPtr<IDXGIDevice>		pIdxgiDevice = nullptr;
	ComPtr<IDXGIAdapter>	pAdapter = nullptr;
	ComPtr<IDXGIFactory>	pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pIdxgiDevice.GetAddressOf());
	pIdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	// SwapChain 생성
	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateTargetView()
{
	// 렌더타겟 텍스처를 SwapChain으로부터 얻어온다
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());

	// 렌더타겟 뷰
	m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTView.GetAddressOf());

	// 뎁스스텐실 텍스처 생성
	D3D11_TEXTURE2D_DESC Desc = {};

	// 뎁스스텔실 픽셀 포맷은 3바이트의 Depth와 1바이트의 Stencil로 구성돼있다
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 뎁스스텐실스테이트 텍스처 해상도는 반드시 렌더타겟 텍스처와 동일해야 한다
	Desc.Width = (UINT)m_vRenderResolution.x;
	Desc.Height = (UINT)m_vRenderResolution.y;

	// 뎁스스텐실 용도의 텍스처
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// CPU 접근 불가
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	// 샘플링
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	// 저퀄리티 버전의 사본 생성여부 (1 == 생성하지 않음)
	Desc.MipLevels = 1;
	Desc.MiscFlags = 0;

	Desc.ArraySize = 1;

	if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DSTex.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 뎁스스텐실 뷰
	m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSView.GetAddressOf());

	// OM(Output Merge State)에 렌더타겟 뷰와 뎁스스텐실 텍스처를 전달
	m_Context->OMSetRenderTargets(1, m_RTView.GetAddressOf(), m_DSView.Get());

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer;
	m_arrCB[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform), 1);

	return S_OK;
}

int CDevice::CreateRasterizerState()
{
	// RasterizerState의 기본값은 CULL_BACK이므로 CULL_BACK 상태를 따로 생성할 필요는 없다
	m_arrRS[(UINT)RS_TYPE::CULL_BACK] = nullptr;

	HRESULT Result = S_OK;

	D3D11_RASTERIZER_DESC tDesc = {};

	// CULL_FRONT
	tDesc.CullMode = D3D11_CULL_FRONT;
	tDesc.FillMode = D3D11_FILL_SOLID;
	Result = DEVICE->CreateRasterizerState(&tDesc, m_arrRS[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	// CULL_NONE
	tDesc.CullMode = D3D11_CULL_NONE;
	tDesc.FillMode = D3D11_FILL_SOLID;
	Result = DEVICE->CreateRasterizerState(&tDesc, m_arrRS[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	// WIRE_FRAME
	tDesc.CullMode = D3D11_CULL_NONE;
	tDesc.FillMode = D3D11_FILL_WIREFRAME;
	Result = DEVICE->CreateRasterizerState(&tDesc, m_arrRS[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());
	if (FAILED(Result))	{ return E_FAIL; }

	return S_OK;
}

int CDevice::CreateDepthStencilState()
{
	m_arrDS[(UINT)DS_TYPE::LESS] = nullptr;

	HRESULT Result = S_OK;

	D3D11_DEPTH_STENCIL_DESC tDesc = {};

	// Less Equal
	tDesc.DepthEnable = true;
	tDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.StencilEnable = false;
	Result = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf());
	if (FAILED(Result))	{ return E_FAIL; }

	// Greater
	tDesc.DepthEnable = true;
	tDesc.DepthFunc = D3D11_COMPARISON_GREATER;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.StencilEnable = false;
	Result = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::GRATER].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	// Greater Equal
	tDesc.DepthEnable = true;
	tDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.StencilEnable = false;
	Result = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::GRATER_EQUAL].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	// No Test
	tDesc.DepthEnable = false;
	tDesc.DepthFunc = D3D11_COMPARISON_NEVER;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.StencilEnable = false;
	Result = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::NO_TEST].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	// No Write
	tDesc.DepthEnable = true;
	tDesc.DepthFunc = D3D11_COMPARISON_LESS;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	tDesc.StencilEnable = false;
	Result = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::NO_WRITE].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	// No Test No Write
	tDesc.DepthEnable = false;
	tDesc.DepthFunc = D3D11_COMPARISON_NEVER;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	tDesc.StencilEnable = false;
	Result = DEVICE->CreateDepthStencilState(&tDesc, m_arrDS[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());
	if (FAILED(Result)) { return E_FAIL; }

	return S_OK;
}

int CDevice::CreateBlendState()
{
	m_arrBS[(UINT)BS_TYPE::DEFAULT] = nullptr;

	D3D11_BLEND_DESC tDesc = {};

	// AlphaBlend
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

void CDevice::ClearRenderTarget(float(&Color)[4])
{
	m_Context->ClearRenderTargetView(m_RTView.Get(), Color);
	m_Context->ClearDepthStencilView(m_DSView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
	m_SwapChain->Present(0, 0);
}
