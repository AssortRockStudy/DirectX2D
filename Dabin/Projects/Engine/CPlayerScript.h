#pragma once
#include "CScript.h"

// =======================================
// CPlayerScript: Player ±¸ÇöºÎ
// =======================================
// imp01. player controller

class CPlayerScript :
    public CScript
{
private:
    float   m_Speed;

public:
    virtual void tick() override;

public:
    CPlayerScript();
    ~CPlayerScript();
};

