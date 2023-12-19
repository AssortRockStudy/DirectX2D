#pragma once
#include "CScript.h"

// =======================================
// CCameraMoveScript: Camera 이동 기능 구현
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

