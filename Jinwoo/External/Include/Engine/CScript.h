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
    UINT        m_iScriptType;

public:
    // final을 붙여 스크립트를 상속받는 클래스에서는 finaltick을 사용하지 않겠다고 명시
    virtual void finaltick() final {}

public:
    CScript();
    ~CScript();
};

