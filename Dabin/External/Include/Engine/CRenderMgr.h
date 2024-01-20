#pragma once
#include "singleton.h"
#include "CTexture.h"
// =======================================
// CRenderMgr: Render 전담
// =======================================

class CCamera;
class CLight2D;
class CGameObject;
class CStructuredBuffer;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);

private:
    vector<CCamera*>        m_vecCam;       // cam은 componets라 여러개 있을 수 있음
    Ptr<CTexture>           m_PostProcessTex;
    vector<CLight2D*>       m_vecLight2D;
    CStructuredBuffer*      m_Light2DBuffer;
    list<tDebugShapeInfo>   m_DbgShapeInfo;
    CGameObject*            m_pDbgObj;
    bool                    m_DebugPosition;

public:
    void init();
    void tick();
    void render();
    void render_debug();

    void UpdatePipeline();
    void Clear();
    void CopyRenderTargetToPostProcessTarget();

public:
    void RegisterCamera(CCamera* _Cam, int _idx);
    void RegisterLight2D(CLight2D* _Light) { m_vecLight2D.push_back(_Light); }
    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_DbgShapeInfo.push_back(_info); }
    void SetDebugPosition(bool _OnOff) { m_DebugPosition = _OnOff; }

    Ptr<CTexture> GetPostProcessTex() { return m_PostProcessTex; }
    bool IsDebugPosition() { return m_DebugPosition; }
};

