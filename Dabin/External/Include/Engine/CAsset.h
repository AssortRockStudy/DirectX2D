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
    virtual int Load(const wstring& _strFilePath) { return E_FAIL; } // private: Asset Mgr로만 공개
    void AddRef() { ++m_RefCount; }
    void SubRef() { --m_RefCount; }
    void Release() { --m_RefCount;
        if (m_RefCount <= 0) delete this;
    }

    // getter & setter
public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

private:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }
    int GetRefCount() { return m_RefCount; }
    ASSET_TYPE GetType() { return m_Type; }

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();

    friend class CAssetMgr;
};