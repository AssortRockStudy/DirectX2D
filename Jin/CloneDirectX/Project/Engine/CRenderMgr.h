#pragma once
#include "singleton.h"

#include "CTexture.h"
class CCamera;
class CGameObject;
class CLight2D;
class CStructuredBuffer;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLETON(CRenderMgr);


private:
    vector<CCamera*>    m_vecCam;
    Ptr<CTexture>           m_PostProcessTex;
    CStructuredBuffer* m_Light2DBuffer;
    vector<CLight2D*>   m_vecLight2D;
    list<tDebugShapeInfo> m_DbgShapeInfo;
    CGameObject* m_pDebugObj;
    bool m_DebugPosition;

public:
    void RegisterCamera(CCamera* _Cam, int _Idx);
    void AddDebugShapeInfo(const tDebugShapeInfo& _info)   {  m_DbgShapeInfo.push_back(_info);  }

    void SetDebugPosition(bool _OnOff) { m_DebugPosition = _OnOff; }
    bool IsDebugPosition() { return m_DebugPosition; }

    void RegisterLight2D(CLight2D* _Light2D) { m_vecLight2D.push_back(_Light2D); }

public:
    void tick();
    void init();

private:
    void render();
    void render_debug();

    // 리소스 바인딩
    void UpdateData();
    // 리소스 클리어
    void Clear();
};

