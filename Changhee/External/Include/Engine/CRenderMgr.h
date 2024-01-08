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

    bool                    m_bDebugPosition;



public:
    void RegisterCamera(CCamera* _Cam, int _Idx);
    void AddDebugShapeInfo(const tDebugShapeInfo& _info)
    {
        m_DbgShapeInfo.push_back(_info);
    }

    void SetDebugPosition(bool _OnOff) { m_bDebugPosition = _OnOff; }
    bool IsDebugPosition() { return m_bDebugPosition; }
public:
    void init();
    void tick();

private:
    void render();
    void render_debug();
};