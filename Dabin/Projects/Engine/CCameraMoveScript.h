#pragma once
#include "CScript.h"

// =======================================
// CCameraMoveScript: Camera �̵� ��� ����
// =======================================

class CCameraMoveScript :
    public CScript
{
private:
    float m_CamSpeed;

private:
    void MoveOrthographic();
    void MovePerspective();

public:
    virtual void tick();

public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

