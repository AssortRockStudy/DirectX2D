#pragma once
#include "singleton.h"
#include "CMesh.h"
#include "CGraphicsShader.h"

// =======================================
// AssetMgr: Asset(resource) 생성, 관리
// =======================================

class CAsset;
class CMesh;
class CGraphicsShader;

class CAssetMgr :
    public CSingleton<CAssetMgr>
{
    SINGLE(CAssetMgr)

private:
    unordered_map<wstring, CAsset*> m_hashAsset[(UINT)ASSET_TYPE::END]; // hash를 ASSET_TYPE마다 만들어 관리

public:
    void init();

public:
    template<typename T>
    void AddAsset(const wstring& _strKey, T* _Asset);

    template<typename T>
    T* FindAsset(const wstring& _strKey);
};

template<typename T>
ASSET_TYPE GetAssetType()
{
    const type_info& info = typeid(T);  // typeid: 런타임에 개체 형식 확인 가능
    ASSET_TYPE Type = ASSET_TYPE::END;

    if (&info == &typeid(CMesh))
        Type = ASSET_TYPE::MESH;
    else if (&info == &typeid(CGraphicsShader))
        Type = ASSET_TYPE::GRAPHICS_SHADER;

    return Type;
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, T* _Asset)
{
    ASSET_TYPE Type = GetAssetType<T>();

    unordered_map<wstring, CAsset*>::iterator iter = m_hashAsset[(UINT)Type].find(_strKey);
    assert(iter == m_hashAsset[(UINT)Type].end());

    m_hashAsset[(UINT)Type].insert(make_pair(_strKey, _Asset));
}

template<typename T>
inline T* CAssetMgr::FindAsset(const wstring& _strKey)
{
    ASSET_TYPE Type = GetAssetType<T>();
    unordered_map<wstring, CAsset*>::iterator iter = m_hashAsset[(UINT)Type].find(_strKey);

    if (iter == m_hashAsset[(UINT)Type].end())
        return nullptr;

    return (T*)iter->second;
}
