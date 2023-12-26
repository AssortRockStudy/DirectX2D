#pragma once
#include "CScript.h"


class CCameraMoveScript :
    public CScript
{
private:
    float   m_CamSpeed;

private:
    void MoveOrthographic();
    void MovePerspective();

public:
    virtual void tick();

public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

