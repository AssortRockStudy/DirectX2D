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
	// 1. �̹��� ���� ScratchImage�� �ε�
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

	// 2. DX texture ��ü, ShaderResourceView ����
	// - 2.1. DX texture ��ü ���� (ID3D11Texture2D)
	// - 2.1.1. �ε��� ������ ���� (Image File -> ScratchImage -> ID3D11Texture2D)
	// - 2.2. ������ texture�� ShaderResourceView ���� (Image File -> ScratchImage -> ID3D11Texture2D -> ShaderResourceView)
	CreateShaderResourceView(DEVICE, m_Image.GetImages(), m_Image.GetImageCount(), m_Image.GetMetadata(), m_SRV.GetAddressOf());

	// ShaderResourceView�� (SRV��) texture ��ü�� �˾Ƴ�
	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

	// texture ��ü�� ���� �� ���� �ɼ�(desc) ������ ������
	m_Tex2D->GetDesc(&m_Desc);

	return S_OK;
}

// Rendering Pipeline���� �ѱ�
void CTexture::UpdatePipeline(int _registerNum)
{
	CONTEXT->VSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->HSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->DSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
}

// Rendering Pipeline �ʱ�ȭ
void CTexture::ClearPipeline(int _registerNum)
{
	ID3D11ShaderResourceView* pSRV = nullptr;

	CONTEXT->VSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(_registerNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(_registerNum, 1, &pSRV);
}
