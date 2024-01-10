#pragma once
#include "CScript.h"


class CBackgroundScript :
    public CScript
{


public:
    virtual void tick() override;

    Vec3 Rotate(Vec3 _vDir, float _angle);

public:
    CBackgroundScript();
    ~CBackgroundScript();
};

