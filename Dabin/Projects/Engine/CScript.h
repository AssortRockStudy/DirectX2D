#pragma once
#include "CComponent.h"

// =======================================
// CScript: 모든 scprit의  parent class
// =======================================
// - 세세한 게임 구현부는 Scripts class를 상속한 scripts를 작성해 구현

class CScript :
    public CComponent
{
private:
    UINT    m_iScriptType;

public:
    virtual void finaltick() final {}

public:
    CScript();
    ~CScript();
};