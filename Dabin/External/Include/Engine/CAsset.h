#pragma once
#include "CEntity.h"
#include "Ptr.h"

// =======================================
// CAsset: 모든 Asset이 상속하는 parent class
// =======================================
// - model 등 재활용 가능한 resource는 asset으로 취급
// - 메모리 관리: reference count 관리
// -- ref count가 1(자기자신)이 되면 날리며 실시간으로 최소한의 메모리 유지

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
    void Release() { if (--m_RefCount <= 0) delete this; }

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

    template <typename T>
    friend class Ptr;
};