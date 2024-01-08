#pragma once
#include "CComponent.h"

#include "CTexture.h"

class CAnim;

class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim*>                m_mapAnim;
    CAnim*                              m_CurAnim;
    bool                                m_bRepeat;

public:
    virtual void finaltick() override;

    void UpdateData();
    static void Clear();

    // _LeftTop, _SliceSize, _Offset : Pixel Unit
    void Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vOffsetSize, int _iFrmCount, float _FPS);
    CAnim* FindAnim(const wstring& _strKey);



    void Play(const wstring& _srtKey);

public:
    CAnimator2D();
    ~CAnimator2D();
};

