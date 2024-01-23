#include "pch.h"
#include "CAnimator2D.h"

#include "CPathMgr.h"
#include "CAnim.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{
}

CAnimator2D::~CAnimator2D()
{
	Delete_Map(m_mapAnim);
}


void CAnimator2D::finaltick()
{
	if (nullptr == m_CurAnim)
	{
		return;
	}

	if (m_CurAnim->IsFinish() && m_bRepeat)
	{
		m_CurAnim->Reset();
	}

	m_CurAnim->finaltick();
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_CurAnim)
	{
		return;
	}

	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{
	CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS)
{
	CAnim* pAnim = FindAnim(_strKey);

	assert(!pAnim);

	pAnim = new CAnim;
	pAnim->Create(this, _AtlasTex, _LeftTop, _vSliceSize, _OffsetSize, _Background, _FrmCount, _FPS);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

void CAnimator2D::CreateFrm(const wstring& _strKey, Ptr<CTexture> _AtlasTex, vector<tAnimFrm> _vecAnimFrm)
{
	CAnim* pAnim = FindAnim(_strKey);

	assert(!pAnim);

	pAnim = new CAnim;
	pAnim->CreateFrm(this, _AtlasTex, _vecAnimFrm);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

CAnim* CAnimator2D::FindAnim(const wstring& _strKey)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator2D::Play(const wstring& _strAnimName, bool _bRepeat)
{
	CAnim* pAnim = FindAnim(_strAnimName);
	
	if (nullptr == pAnim)
	{
		return;
	}

	m_bRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();
}

void CAnimator2D::SaveAnimations(const wstring& _strRelativePath)
{
	wstring strFolderPath = CPathMgr::GetContentPath();
	strFolderPath += _strRelativePath;

	for (const auto& pair : m_mapAnim)
	{
		wstring strFilePath = strFolderPath + L"\\" + pair.first + L".txt";
		wstring strKey = pair.first;
		if (!pair.second->Save(strFilePath, strKey))
		{
			MessageBox(nullptr, L"Animation 생성 실패", L"Animation 생성 실패", MB_OK);
		}
	}
}

void CAnimator2D::LoadAnimation(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	CAnim* pNewAnim = new CAnim;

	if (!pNewAnim->Load(strFilePath))
	{
		MessageBox(nullptr, L"Animation Load 실패", L"Animation Load 실패", MB_OK);
		delete pNewAnim;
		return;
	}

	pNewAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
}

map<wstring, CAnim*> CAnimator2D::GetAnimList()
{
	return m_mapAnim;
}
