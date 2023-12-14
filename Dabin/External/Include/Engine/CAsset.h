#pragma once
#include "CEntity.h"

// =======================================
// CAsset: 모든 Asset이 상속하는 parent class
// =======================================
// - model 등 재활용 가능한 resource는 asset으로 취급

class CAsset :
    public CEntity
{
private:
    wstring             m_Key;
    wstring             m_RelativePath;
    int                 m_RefCount;
    const ASSET_TYPE    m_Type;

private:
    void AddRef() { ++m_RefCount; }
    void SubRef() { --m_RefCount; }

    // getter & setter
private:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }
    int GetRefCount() { return m_RefCount; }

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();
};

