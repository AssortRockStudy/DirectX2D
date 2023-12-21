#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
public:
    virtual void tick();

public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

