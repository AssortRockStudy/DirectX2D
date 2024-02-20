#pragma once
#include <Engine\CScript.h>

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

    CLONE(CCameraMoveScript);

public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

