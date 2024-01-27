#include "pch.h"
#include "CAssetMgr.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	// Ptr 사용해 refcount 1이 되면 할당 해제하므로 AssetMgr가 종료시 처리하지 않아도 됨
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height, DXGI_FORMAT _Format, UINT _Flag, D3D11_USAGE _Usage)
{
	Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);
	assert(!pTex.Get());

	pTex = new CTexture;
	if (FAILED(pTex->Create(_Width, _Height, _Format, _Flag, _Usage)))
	{
		MessageBox(nullptr, L"Failed to Create Texture", L"Faile to Create Resource", MB_OK);
		return nullptr;
	}
	
	AddAsset<CTexture>(_strKey, pTex.Get());
	return pTex;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _tex2D)
{
	Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);
	assert(!pTex.Get());

	pTex = new CTexture;
	if (FAILED(pTex->Create(_tex2D)))
	{
		MessageBox(nullptr, L"Failed to Create Texture", L"Faile to Create Resource", MB_OK);
		return nullptr;
	}

	AddAsset<CTexture>(_strKey, pTex.Get());
	return pTex;
}

void CAssetMgr::GetAssetName(ASSET_TYPE _Type, vector<string>& _out)
{
	for (const auto& pair : m_hashAsset[(UINT)_Type])
		_out.push_back(wstrToStr(pair.first));
}
