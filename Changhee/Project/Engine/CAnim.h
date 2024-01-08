#pragma once
#include "CEntity.h"

#include "CTexture.h"

struct tAnimFrm
{
    Vec2        vLeftTop;
    Vec2        vSlice;
    Vec2        vOffset;
    Vec2        vBackground;
    float       Duration;
};

class CAnimator2D;

class CAnim :
    public CEntity
{
private:
    CAnimator2D*        m_Animator;
    Ptr<CTexture>       m_AtlasTex;

    vector<tAnimFrm>    m_vecFrm;
    int                 m_iCurFrmIdx;
    float               m_fAccTime;
    bool                m_bFinish;


public:
    void finaltick();
    void UpdateData();
    static void Clear();

public:
    void Create(CAnimator2D* _Animator, Ptr<CTexture> _Atlas, Vec2 _vLeftTop
        , Vec2 _vSliceSize, Vec2 _vOffset, Vec2 _vBackground, int _FrmCount, float _FPS);

public:
    CAnim();
    ~CAnim();
};

