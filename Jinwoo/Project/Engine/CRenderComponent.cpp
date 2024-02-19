#include "pch.h"
#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _Type)
	: CComponent(_Type)
{
}

CRenderComponent::CRenderComponent(const CRenderComponent& _OriginRenderCom)
	: CComponent(_OriginRenderCom)
	, m_Mesh(_OriginRenderCom.m_Mesh)
	, m_SharedMtrl(_OriginRenderCom.m_SharedMtrl)
{
	// 원본 오브젝트가 공유재질을 참조하고 있고, 현재 사용재질은 공유재질이 아닌 경우
	if (_OriginRenderCom.m_SharedMtrl != _OriginRenderCom.m_CurMtrl)
	{
		assert(_OriginRenderCom.m_DynamicMtrl.Get());

		// 복사 렌더 컴포넌트도 별도의 동적재질을 생성
		GetDynamicMaterial();
	}
	else
	{
		m_CurMtrl = m_SharedMtrl;
	}
}

CRenderComponent::~CRenderComponent()
{
}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	// 재질이 변경되면 기존에 복사본 받아둔 DynamicMaterial 을 삭제
	m_CurMtrl = m_SharedMtrl = _Mtrl;
	m_DynamicMtrl = nullptr;
}


Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	// 이미 동적재질을 보유하고 있으면 해당 동적재질 리턴
	if (nullptr != m_DynamicMtrl)
		return m_DynamicMtrl;

	// 공유재질이 있다면
	if (nullptr != m_SharedMtrl)
	{
		// 공유재질을 복사해서 동적재질을 만들고 그걸 현재 사용재질로 설정
		m_CurMtrl = m_DynamicMtrl = m_SharedMtrl->Clone();
		return m_DynamicMtrl;
	}

	return nullptr;
}

void CRenderComponent::RestoreMaterial()
{
	m_CurMtrl = m_SharedMtrl;
}