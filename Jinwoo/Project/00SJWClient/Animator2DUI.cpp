#include "pch.h"
#include "Animator2DUI.h"

#include "EditAnimator.h"

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
{
	SetSize(ImVec2(0.f, 100.f));
	SetComponentTitle("Animator2D");
}

Animator2DUI::~Animator2DUI()
{
}

void Animator2DUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	if (ImGui::Button("Edit Animation", ImVec2(130, 20)))
	{
		EditAnimator* pEdit = (EditAnimator*)CImGuiMgr::GetInst()->FindUI("##EditAnimation");
		CGameObject* pTarget = GetTargetObject();
		pEdit->SetTaretObject(pTarget);
		pEdit->Activate();
	}

	map<wstring, CAnim*> animList = GetTargetObject()->Animator2D()->GetAnimList();

	static vector<string> animNames;

	if (!animList.empty())
	{
		for (const auto& pair : animList)
		{
			wstring animName = pair.first;
			string animNameStr = ToString(animName);

			// 중복 체크
			if (std::find(animNames.begin(), animNames.end(), animNameStr) == animNames.end())
			{
				animNames.push_back(animNameStr);
			}
		}

		static int selectedIndex = 0;
		ImGui::PushItemWidth(150);
		if (ImGui::BeginCombo("##AnimList", animNames[selectedIndex].c_str()))
		{
			for (int i = 0; i < (int)animNames.size(); ++i)
			{
				bool isSelected = (selectedIndex == i);

				if (ImGui::Selectable(animNames[i].c_str(), isSelected))
				{
					selectedIndex = i;
				}

				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		// 현재 선택된 애니메이션을 실행하는 버튼
		if (ImGui::Button("Play Animation"))
		{
			if (selectedIndex >= 0 && selectedIndex < animNames.size())
			{
				string selectedAnimName = animNames[selectedIndex];
				wstring selectedAnimNameW = ToWString(selectedAnimName);

				// 선택된 애니메이션 실행 코드 추가
				GetTargetObject()->Animator2D()->Play(selectedAnimNameW);
			}
		}
	}
}