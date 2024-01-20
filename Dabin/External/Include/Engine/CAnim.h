#pragma once
#include "CEntity.h"
#include "CTexture.h"
// =======================================
// CAnim: Animation 단위 (Components가 소유하는 정보)
// =======================================
class CAnimator2D;

struct tAnimFrm
{
    Vec2    vLeftTopUV;
    Vec2    vCutSizeUV;
    Vec2    vOffsetUV;
    Vec2    vBackgroundSize;
    float   fDuration;
};

class CAnim :
    public CEntity
{
private:
    CAnimator2D*        m_Animator;
    Ptr<CTexture>       m_AtlasTex;
    vector<tAnimFrm>    m_vecFrm;
    int                 m_CurFrmIdx;
    float               m_AccTime;
    bool                m_bFinish;

public:
    void finaltick();
    void UpdatePipeline();
    static void Clear();
    void Create(CAnimator2D* _Animator, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vOffset, Vec2 _vCutSize, Vec2 _vBackground, int _FrmCount, float _FPS);

public:
    CAnim();
    ~CAnim();
};

