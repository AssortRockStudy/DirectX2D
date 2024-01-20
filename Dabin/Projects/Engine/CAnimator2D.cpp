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

void CAnimator2D::UpdatePipeline()
{
    m_CurAnim->UpdatePipeline();
}

void CAnimator2D::Clear()
{
    CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vOffset, Vec2 _vCutSize, Vec2 _vBackgroundSize, int _FrmCount, float _FPS)
{
    CAnim* pAnim = FindAnim(_strKey);
    assert(!pAnim);

    pAnim = new CAnim;
    pAnim->Create(this, _AtlasTex, _vLeftTop, _vOffset, _vCutSize, _vBackgroundSize, _FrmCount, _FPS);
    m_mapAnim.insert({ _strKey, pAnim });
}

CAnim* CAnimator2D::FindAnim(const wstring& _strAnimName)
{
    unordered_map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strAnimName);
    if (iter != m_mapAnim.end())
        return iter->second;
    return nullptr;
}

void CAnimator2D::Play(const wstring& _strAnimName)
{
    CAnim* pAnim = FindAnim(_strAnimName);
    if (!pAnim)
        return;
    m_CurAnim = pAnim;
}