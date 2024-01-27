#include "pch.h"
#include "UIInspectorPannel.h"
#include "Engine/CTransform.h"
#include "UITransform.h"
#include "UIMeshRender.h"

UIInspectorPannel::UIInspectorPannel()
	: UI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComp{}
{
	// 자식 UI 생성
	m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM] = new UITransform;
	m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM]->SetInspector(this);
	AddChild(m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER] = new UIMeshRender;
	m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER]->SetInspector(this);
	AddChild(m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER]);
}

UIInspectorPannel::~UIInspectorPannel()
{
}

void UIInspectorPannel::tick()
{
}

void UIInspectorPannel::render_update()
{
	if (!m_TargetObject)
		return;
	
	string strName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
	ImGui::Text(strName.c_str());
}

void UIInspectorPannel::SetTargetObject(CGameObject* _Object)
{
	m_TargetObject = _Object;

	for (size_t i = 0; i < (size_t)COMPONENT_TYPE::END; ++i)
	{
		if (m_arrComp[i])
			m_arrComp[i]->DecideActivation();
	}
}
