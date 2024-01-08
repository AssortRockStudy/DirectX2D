#include "pch.h"
#include "CRenderMgr.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include "CStructuredBuffer.h"

void CRenderMgr::init()
{
	Vec4 arr[3] =
	{
		Vec4(1.f, 0.f, 0.f, 1.f),
		Vec4(0.f, 1.f, 0.f, 1.f),
		Vec4(0.f, 0.f, 1.f, 1.f)
	};

	m_Light2DBuffer = new CStructuredBuffer;
	m_Light2DBuffer->Create(sizeof(Vec4), 2, SB_TYPE::READ_ONLY, true);

	if (m_Light2DBuffer->GetElementCount() < 3)
	{
		m_Light2DBuffer->Create(sizeof(Vec4), 10, SB_TYPE::READ_ONLY, true);
	}

	m_Light2DBuffer->SetData(arr, 3);
	m_Light2DBuffer->UpdateData(14);

	Vec4 arrTest[3] = {};
	// 만약 ElementCount가 SetData()의 ElementCount보다 크게 만들어져 있을경우
	// GetData()에서 얼마나 데이터를 가져올지 정해주지 않으면 다른 메모리까지 참조하여 가져오게 된다
	m_Light2DBuffer->GetData(arrTest, 3);

	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);
}
