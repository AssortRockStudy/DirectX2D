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
    void UpdateData();
    static void Clear();
    void Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS);
    CAnim* FindAnim(const wstring& _strKey);
    void Play(const wstring& _strAnimName, bool _bRepeat = true);

public:
    CAnimator2D();
    ~CAnimator2D();
};

