#include "pch.h"
#include "TransformUI.h"

#include <Engine\CTransform.h>

TransformUI::TransformUI()
	: ComponentUI("Transform", "##Transform", COMPONENT_TYPE::TRANSFORM)
{
	SetSize(ImVec2(0.f, 115.f));
	SetComponentTitle("Transform");
}

TransformUI::~TransformUI()
{
}

void TransformUI::render_update()
{
	if (nullptr == GetTargetObject())
	{
		return;
	}

	ComponentUI::render_update();

	Vec3 vPos = GetTargetObject()->Transform()->GetRelativePos();
	Vec3 vScale = GetTargetObject()->Transform()->GetRelativeScale();
	Vec3 vRot = GetTargetObject()->Transform()->GetRelativeRotation();
	vRot.ToDegree();


	ImGui::Text("Position");
	ImGui::SameLine(0, 20);	ImGui::PushItemWidth(80);
	ImGui::Text("x"); ImGui::SameLine(); ImGui::DragFloat("##Posx", &vPos.x); ImGui::SameLine();
	ImGui::Text("y"); ImGui::SameLine(); ImGui::DragFloat("##Posy", &vPos.y); ImGui::SameLine();
	ImGui::Text("z"); ImGui::SameLine(); ImGui::DragFloat("##Posz", &vPos.z);
	//ImGui::DragFloat3("##Relative Position", vPos);

	ImGui::Text("Scale");
	ImGui::SameLine(0, 41);	ImGui::PushItemWidth(80);
	ImGui::Text("x"); ImGui::SameLine(); ImGui::DragFloat("##Scalex", &vScale.x); ImGui::SameLine();
	ImGui::Text("y"); ImGui::SameLine(); ImGui::DragFloat("##Scaley", &vScale.y); ImGui::SameLine();
	ImGui::Text("z"); ImGui::SameLine(); ImGui::DragFloat("##Scalez", &vScale.z);
	//ImGui::DragFloat3("##Relative Scale", vScale);

	ImGui::Text("Rotation");
	ImGui::SameLine(0, 20);	ImGui::PushItemWidth(80);
	ImGui::Text("x"); ImGui::SameLine(); ImGui::DragFloat("##Rotx", &vRot.x); ImGui::SameLine();
	ImGui::Text("y"); ImGui::SameLine(); ImGui::DragFloat("##Roty", &vRot.y); ImGui::SameLine();
	ImGui::Text("z"); ImGui::SameLine(); ImGui::DragFloat("##Rotz", &vRot.z);
	//ImGui::DragFloat3("##Relative Rotation", vRot);

	vRot.ToRadian();

	GetTargetObject()->Transform()->SetRelativePos(vPos);
	GetTargetObject()->Transform()->SetRelativeScale(vScale);
	GetTargetObject()->Transform()->SetRelativeRotation(vRot);

	// Absolute 체크
	bool bAbsolute = GetTargetObject()->Transform()->IsAbsolute();
	ImGui::Text("Scale Absolute");
	ImGui::SameLine();
	ImGui::Checkbox("##TransformAbsolute", &bAbsolute);
	GetTargetObject()->Transform()->SetAbsolute(bAbsolute);
}