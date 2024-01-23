#pragma once
#include "singleton.h"

#include "CTexture.h"

class CGameObject;
class CCamera;
class CLight2D;

class CStructuredBuffer;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    vector<CCamera*>        m_vecCam;
    vector<CLight2D*>       m_vecLight2D;

    Ptr<CTexture>           m_PostProcessTex;

    CStructuredBuffer*      m_Light2DBuffer;
    list<tDebugShapeInfo>   m_DbgShapeInfo;
    CGameObject*            m_DebugObj;
    bool                    m_bDebugPosition;

public:
    void RegisterCamera(CCamera* _Cam, int _Idx);
    void AddDebugShapeInfo(const tDebugShapeInfo& _info)
    {
        m_DbgShapeInfo.push_back(_info);
    }

    void SetDebugPosition(bool _OnOff) { m_bDebugPosition = _OnOff; }
    bool IsDebugPosition() { return m_bDebugPosition; }

    void RegisterLight2D(CLight2D* _Light2D) { m_vecLight2D.push_back(_Light2D); }

    void CopyRenderTargetToPostProcessTarget();
    Ptr<CTexture> GetPostProcessTex() { return m_PostProcessTex; }

public:
    void init();
    void tick();

private:
    void render();
    void render_debug();

    // 리소스 바인딩
    void UpdateData();

    // 리소스 클리어
    void Clear();
};