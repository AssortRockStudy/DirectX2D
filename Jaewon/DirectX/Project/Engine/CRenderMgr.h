#pragma once
#include "singleton.h"

class CCamera;
class CGameObject;
class CStructuredBuffer;
class CLight2D;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    vector<CCamera*> m_vecCam;
    list<tDebugShapeInfo> m_DbgShapeInfo;
    CGameObject* m_pDebugObj;
    bool m_DebugPosition;
    CStructuredBuffer* m_Light2DBuffer;
    vector<CLight2D*> m_vecLight2D;

public:
    void RegisterCamera(CCamera* _Cam, int _Idx);
    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_DbgShapeInfo.push_back(_info); }
    void SetDebugPosition(bool _OnOff) { m_DebugPosition = _OnOff; }
    bool IsDebugPosition() { return m_DebugPosition; }
    void RegisterLight2D(CLight2D* _Light2D) { m_vecLight2D.push_back(_Light2D); }

public:
    void init();
    void tick();

private:
    void render();
    void render_debug();
    void UpdateData();
    void Clear();
};


