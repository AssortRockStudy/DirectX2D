#include "pch.h"
#include "CAnim.h"
#include "CTimeMgr.h"
#include "CConstBuffer.h"
#include "CDevice.h"
#include "CTexture.h"

CAnim::CAnim()
	: m_Animator(nullptr)
	, m_CurFrmIdx(0)
	, m_AccTime(0.f)
	, m_bFinish(false)
{
}

CAnim::~CAnim()
{
	if (!m_vecFrm.empty())
		m_vecFrm.clear();
}

void CAnim::finaltick()
{
	m_AccTime += DT;
	if (m_AccTime > m_vecFrm[m_CurFrmIdx].fDuration)
	{
		++m_CurFrmIdx;
		if (m_CurFrmIdx >= m_vecFrm.size())
			m_CurFrmIdx = 0;
		m_AccTime = 0.f;
	}
}

void CAnim::UpdatePipeline()
{
	// constant buffer: 현재 프레임 정보
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = true;
	data.vLeftTop = m_vecFrm[m_CurFrmIdx].vLeftTopUV;
	data.vOffset = m_vecFrm[m_CurFrmIdx].vOffsetUV;
	data.vCutSize = m_vecFrm[m_CurFrmIdx].vCutSizeUV;
	data.vBackgroundSize = m_vecFrm[m_CurFrmIdx].vBackgroundSize;

	pCB->SetData(&data);
	pCB->UpdatePipeline();

	// Shader Resource View 등록 (register 10)
	m_AtlasTex->UpdatePipeline(10);
}

void CAnim::Clear()
{
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = false;

	pCB->SetData(&data);
	pCB->UpdatePipeline();
}

void CAnim::Create(CAnimator2D* _Animator, Ptr<CTexture> _AtlasTex, Vec2 _vLeftTop, Vec2 _vOffset, Vec2 _vCutSize, Vec2 _vBackground, int _FrmCount, float _FPS)
{
	m_Animator = _Animator;
	m_AtlasTex = _AtlasTex;

	for (int i = 0; i < _FrmCount; ++i)
	{
		// UV값으로 세팅
		tAnimFrm frm = {};
		frm.vCutSizeUV = Vec2(_vCutSize.x / (float)_AtlasTex->GetWidth(), _vCutSize.y / (float)_AtlasTex->GetHeight());
		frm.vLeftTopUV = Vec2(_vLeftTop.x / (float)_AtlasTex->GetWidth() + frm.vCutSizeUV.x * i, _vLeftTop.y / (float)_AtlasTex->GetHeight());
		frm.vOffsetUV = Vec2(_vOffset.x / (float)_AtlasTex->GetWidth(), _vOffset.y / (float)_AtlasTex->GetHeight());
		frm.fDuration = 1.f / _FPS;
		frm.vBackgroundSize = Vec2(_vBackground.x / (float)_AtlasTex->GetWidth(), _vBackground.y / (float)_AtlasTex->GetHeight());

		m_vecFrm.push_back(frm);
	}
}