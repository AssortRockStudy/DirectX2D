#pragma once
#include "CComponent.h"

#include "CTexture.h"

class CAnim;

class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim*> m_mapAnim;
    CAnim* m_CurAnim;
    bool m_bRepeat;

public:
    virtual void finaltick() override;

    void Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, int _FrmCount, float _FPS);

    CAnim* FindAnim(const wstring& _strKey);

public:
    CAnimator2D();
    ~CAnimator2D();
};

