#pragma once
#include <Engine\CScript.h>

class CBackgroundScript :
    public CScript
{
public:
    virtual void tick() override;

    Vec3 Rotate(Vec3 _vDir, float _angle);

    CLONE(CBackgroundScript);

public:
    CBackgroundScript();
    ~CBackgroundScript();
};

