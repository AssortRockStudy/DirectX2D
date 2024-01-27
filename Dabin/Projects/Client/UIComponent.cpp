#include "pch.h"
#include "UIComponent.h"
#include "UIInspectorPannel.h"

UIComponent::UIComponent(const string& _strName, const string& _ID, COMPONENT_TYPE _Type)
	: UI(_strName, _ID)
	, m_pInspector(nullptr)
	, m_Type(_Type)
{
}

UIComponent::~UIComponent()
{
}

void UIComponent::render()
{
	if (!IsActivate())
		return;

	if (ImGui::CollapsingHeader(this->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		render_update();
		const vector<UI*> vecChild = GetChilds();
		for (size_t i = 0; i < vecChild.size(); ++i)
			vecChild[i]->render();
	}
}

void UIComponent::render_update()
{
}

void UIComponent::DecideActivation()
{
	CGameObject* pTarget = GetInspector()->GetTargetObject();
	if (pTarget && pTarget->GetComponents(m_Type))
		Activate();
	else
		Deactivate();
}
