#pragma once

#include "CEntity.h"


class CAsset :
    public CEntity
{
private:
    wstring              m_Key;
    wstring              m_RelativePath;
    int                  m_RefCount;
    const ASSET_TYPE     m_Type;


public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

private:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

    void AddRef() { ++m_RefCount; }
    void SubRef() { --m_RefCount; }

    int GetRefCount() { return m_RefCount; }
    ASSET_TYPE GetTYPE() { return m_Type; }

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();

};

