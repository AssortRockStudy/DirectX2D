#include "pch.h"
#include "CAssetMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CMaterial.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
}




Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height, DXGI_FORMAT _Format, UINT _Flag, D3D11_USAGE _Usage)
{
	// 생성하려는 텍스처와 동일한 키의 텍스처가 이미 AssetMgr에 있을 경우
	Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);
	assert(!pTex.Get());

	pTex = new CTexture;

	if (FAILED(pTex->Create(_Width, _Height, _Format, _Flag, _Usage)))
	{
		MessageBox(nullptr, L"텍스처 생성 실패", L"리소스 생성 실패", MB_OK);
		return nullptr;
	}

	AddAsset<CTexture>(_strKey, pTex.Get());

	return pTex;
}


Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _tex2D)
{
	// 생성하려는 텍스처와 동일한 키의 텍스처가 이미 AssetMgr에 있을 경우
	Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);
	assert(!pTex.Get());

	pTex = new CTexture;

	if (FAILED(pTex->Create(_tex2D)))
	{
		MessageBox(nullptr, L"텍스처 생성 실패", L"리소스 생성 실패", MB_OK);
		return nullptr;
	}

	AddAsset<CTexture>(_strKey, pTex.Get());

	return pTex;
}
