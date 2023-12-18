#pragma once
#include "CComponent.h"
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

