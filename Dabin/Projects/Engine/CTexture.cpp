#include "pch.h"
#include "CTexture.h"
#include "CDevice.h"

CTexture::CTexture()
	: CAsset(ASSET_TYPE::TEXTURE)
	, m_Desc{}
{
}

CTexture::~CTexture()
{
}

// image file load
int CTexture::Load(const wstring& _strFilePath)
{
	// 1. 이미지 파일 ScratchImage로 로드
	HRESULT hr = S_OK;
	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS_NONE, nullptr, m_Image);
	else if (!wcscmp(szExt, L".tga") || !wcscmp(szExt, L"TGA"))
		hr = LoadFromTGAFile(_strFilePath.c_str(), nullptr, m_Image);
	else
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS_NONE, nullptr, m_Image); // png, bmp, jpg, jpeg ...
		
	if FAILED(hr)
		return E_FAIL;

	// 2. DX texture 객체, ShaderResourceView 생성
	// - 2.1. DX texture 객체 생성 (ID3D11Texture2D)
	// - 2.1.1. 로딩한 데이터 전달 (Image File -> ScratchImage -> ID3D11Texture2D)
	// - 2.2. 생성한 texture로 ShaderResourceView 생성 (Image File -> ScratchImage -> ID3D11Texture2D -> ShaderResourceView)
	CreateShaderResourceView(DEVICE, m_Image.GetImages(), m_Image.GetImageCount(), m_Image.GetMetadata(), m_SRV.GetAddressOf());

	// ShaderResourceView로 (SRV의) texture 객체를 알아냄
	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

	// texture 객체로 사용될 때 사용된 옵션(desc) 정보를 가져옴
	m_Tex2D->GetDesc(&m_Desc);

	return S_OK;
}

// Rendering Pipeline으로 넘김
void CTexture::UpdatePipeline(int _registerNum)
{
	CONTEXT->VSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->HSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->DSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
}

// Rendering Pipeline 초기화
void CTexture::ClearPipeline(int _registerNum)
{
	ID3D11ShaderResourceView* pSRV = nullptr;

	CONTEXT->VSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(_registerNum, 1, &pSRV);
}
