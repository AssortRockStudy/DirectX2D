#pragma once
#include "singleton.h"
// =======================================
// CRenderMgr: Render ����
// =======================================

class CCamera;
class CGameObject;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);

private:
    vector<CCamera*>        m_vecCam;       // cam�� componets�� ������ ���� �� ����
    list<tDebugShapeInfo>   m_DbgShapeInfo;
    CGameObject*            m_pDbgObj;

public:
    void init();
    void tick();
    void render();
    void render_debug();

public:
    void RegisterCamera(CCamera* _Cam, int _idx);
    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_DbgShapeInfo.push_back(_info); }

};

