#pragma once
#include "singleton.h"

#include "CPathMgr.h"
#include "CAsset.h"

#include "CMesh.h"
#include "CComputeShader.h"
#include "CGraphicsShader.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CPrefab.h"

class CAssetMgr :
	public CSingleton<CAssetMgr>
{
	SINGLE(CAssetMgr);

private:
	map<wstring, Ptr<CAsset>>   m_mapAsset[(UINT)ASSET_TYPE::END];

private:
	void CreateDefaultMesh();
	void CreateDefaultGraphicsShader();
	void CreateDefaultComputeShader();
	void CreateDefaultMaterial();

public:
	void init();

public:
	template<typename T>
	const map<wstring, Ptr<CAsset>>& GetAssets();

	const map<wstring, Ptr<CAsset>>& GetAssets(ASSET_TYPE _Type) { return m_mapAsset[(UINT)_Type]; }

	void AddAsset(const wstring& _strKey, CAsset* _Asset);

	template<typename T>
	void AddAsset(const wstring& _strKey, T* _Asset);

	template<typename T>
	Ptr<T> FindAsset(const wstring& _strKey);

	template<typename T>
	Ptr<T> Load(const wstring& _strKey, const wstring& _strRelativePath);

	// _Flag = D3D11_BIND_FLAG
	Ptr<CTexture> CreateTexture(const wstring& _strKey, UINT _Width, UINT _Height, DXGI_FORMAT _Format, UINT _Flag, D3D11_USAGE _Usage = D3D11_USAGE_DEFAULT);
	Ptr<CTexture> CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _tex2D);

public:
	void GetAssetName(ASSET_TYPE _Type, vector<string>& _Out);
};


template<typename T>
ASSET_TYPE GetAssetType()
{
	ASSET_TYPE Type = ASSET_TYPE::END;

	if constexpr (std::is_same_v<CMesh, T>)
		Type = ASSET_TYPE::MESH;

	if constexpr (std::is_same_v<CTexture, T>)
		Type = ASSET_TYPE::TEXTURE;

	if constexpr (std::is_same_v<CGraphicsShader, T>)
		Type = ASSET_TYPE::GRAPHICS_SHADER;

	if constexpr (std::is_same_v<CComputeShader, T>)
		Type = ASSET_TYPE::COMPUTE_SHADER;

	if constexpr (std::is_same_v<CMaterial, T>)
		Type = ASSET_TYPE::MATERIAL;

	if constexpr (std::is_same_v<CPrefab, T>)
		Type = ASSET_TYPE::CPrefab;

	return Type;
}


template<typename T>
inline const map<wstring, Ptr<CAsset>>& CAssetMgr::GetAssets()
{
	ASSET_TYPE Type = GetAssetType<T>();

	return m_mapAsset[(UINT)Type];
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, T* _Asset)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)Type].find(_strKey);

	// map에 Type이 있는 경우
	assert(iter == m_mapAsset[(UINT)Type].end());

	_Asset->SetKey(_strKey);

	m_mapAsset[(UINT)Type].insert(make_pair(_strKey, _Asset));
}

template<typename T>
Ptr<T> CAssetMgr::FindAsset(const wstring& _strKey)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)Type].find(_strKey);

	if (iter == m_mapAsset[(UINT)Type].end())
	{
		return nullptr;
	}

	return (T*)iter->second.Get();
}

template<typename T>
Ptr<T> CAssetMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
	Ptr<T> pAsset = FindAsset<T>(_strKey);

	// 찾으려는 에셋이 이미 있다면
	if (nullptr != pAsset)
	{
		return (T*)pAsset.Get();
	}

	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	pAsset = new T;

	if (FAILED(pAsset->Load(strFilePath)))
	{
		MessageBox(nullptr, L"에셋 로딩 실패", L"에셋 로드 실패", MB_OK);
		pAsset = nullptr;
		return nullptr;
	}

	pAsset->SetKey(_strKey);
	pAsset->SetRelativePath(_strRelativePath);
	AddAsset<T>(_strKey, (T*)pAsset.Get());

	return (T*)pAsset.Get();
}
