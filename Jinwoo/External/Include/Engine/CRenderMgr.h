#pragma once
#include "singleton.h"

class CCamera;
class CGameObject;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);

private:
    vector<CCamera*>        m_vecCam;
    list<tDebugShapeInfo>   m_DbgShapeInfo;
    CGameObject*            m_pDebugObj;
    bool                    m_DebugPosition;

public:
    void RegisterCamera(CCamera* _Cam, int _Idx);
    void AddDebugShapeInfo(const tDebugShapeInfo& _Info)
    {
        m_DbgShapeInfo.push_back(_Info);
    }

    void SetDebugPosition(bool _IsValid) { m_DebugPosition = _IsValid; }
    bool IsDebugPosition() { return m_DebugPosition; }

public:
    void init();
    void tick();

private:
    void render();
    void render_debug();
};

