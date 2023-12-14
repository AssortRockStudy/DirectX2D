#pragma once
#include "singleton.h"
class CTimeMgr :
    public CSingleton<CTimeMgr>
{
    SINGLE(CTimeMgr)

private:
    LARGE_INTEGER   m_Frequency; // LARGE_INTGER: 8byte long long type 정수로 취급
    LARGE_INTEGER   m_PrevCount;
    LARGE_INTEGER   m_CurCount;
    float           m_DeltaTime;

    UINT            m_iCall;
    float           m_fTime;

public:
    void init();
    void tick();

    float GetDeltaTime() { return m_DeltaTime; }
};

