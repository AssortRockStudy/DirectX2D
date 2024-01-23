#include "pch.h"
#include "ComponentUI.h"

ComponentUI::ComponentUI(const string& _strName, const string& _ID, COMPONENT_TYPE _Type)
	: UI(_strName, _ID)
	, m_TargetObject(nullptr)
	, m_Type(_Type)
{
}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::SetTargetObject(CGameObject* _Target)
{
	m_TargetObject = _Target;

	// 타겟 오브젝트 없을 때, 타겟 오브젝트가 해당 컴포넌트 안 갖고 있으면
	// 컴포너트 UI 비활성화
	if (nullptr == m_TargetObject)
		Deactivate();
	else
	{
		if (!m_TargetObject->GetComponent(m_Type))
			Deactivate();
		else
			Activate();
	}
}

void ComponentUI::render_update()
{
	ImGui::Separator();

	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

	ImGui::Button(m_ComponentTitle.c_str());

	ImGui::PopStyleColor(3);
	ImGui::PopID();
}


