#pragma once
#include "CComponent.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CGameObject.h"
#include "components.h"

class CScript :
    public CComponent
{
private:
    UINT m_iScriptType;

public:
    virtual void finaltick() final {}

public:
    void Destroy();

public:
    CScript();
    ~CScript();
};