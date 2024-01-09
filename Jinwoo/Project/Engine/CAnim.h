#pragma once
#include "CEntity.h"

#include "CTexture.h"

struct tAnimFrm
{
    Vec2 vLeftTop;
    Vec2 vSlice;
    Vec2 vOffset;
    Vec2 vBackground;
    float Durateion;
};

class CAnimator2D;

class CAnim :
    public CEntity
{
private:
    CAnimator2D*        m_Animator;
    vector<tAnimFrm>    m_vecFrm;
    int                 m_CurFrmIdx;
    bool                m_bFinish;
    float               m_AccTime;

    Ptr<CTexture>       m_AtlasTex;

public:
    void finaltick();
    void UpdateData();

    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_bFinish = false; 
        m_CurFrmIdx = 0;
        m_AccTime = 0.f;
    }

    static void Clear();
    void Create(CAnimator2D* _Animator, Ptr<CTexture> _Atlas, Vec2 _vLeftTop, Vec2 _vSliceSize,
                Vec2 _vOffset, Vec2 _vBackground, int _FrmCount, float _FPS);

public:
    CAnim();
    ~CAnim();
};

