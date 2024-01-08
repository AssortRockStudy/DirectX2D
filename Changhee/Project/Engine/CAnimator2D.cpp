#include "pch.h"
#include "CAnimator2D.h"

#include "CAnim.h"



CAnimator2D::CAnimator2D()
    : CComponent(COMPONENT_TYPE::ANIMATOR2D)
    , m_CurAnim(nullptr)
    , m_bRepeat(false)
{
}

CAnimator2D::~CAnimator2D()
{
    Delete_Map(m_mapAnim);
}

void CAnimator2D::finaltick()
{
    m_CurAnim->finaltick();
}

void CAnimator2D::UpdateData()
{
    m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{
    CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop
    , Vec2 _vSliceSize, Vec2 _vOffsetSize, int _iFrmCount, float _FPS)
{
    CAnim* pAnim = FindAnim(_strKey);
    assert(!pAnim);

    pAnim = new CAnim;
    pAnim->Create(this, _AtlasTex, _vLeftTop, _vSliceSize, _vOffsetSize, _iFrmCount, _FPS);
    m_mapAnim.insert(make_pair(_strKey, pAnim));
    

}

CAnim* CAnimator2D::FindAnim(const wstring& _strKey)
{
    map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strKey);

    if (iter == m_mapAnim.end())
        return nullptr;

    return iter->second;
}


void CAnimator2D::Play(const wstring& _srtKey)
{
    CAnim* pAnim = FindAnim(_srtKey);
    if (nullptr == pAnim)
        return;

    m_CurAnim = pAnim;
}