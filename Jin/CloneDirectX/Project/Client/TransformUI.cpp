#include "pch.h"
#include "TransformUI.h"
#include <Engine/CTransform.h>

TransformUI::TransformUI()
	: ComponentUI("Transform", "##Transform", COMPONENT_TYPE::TRANSFORM)
{
	SetComopnentTitle("Transform");
	SetSize(ImVec2(0.f, 100.f));
}

TransformUI::~TransformUI()
{
}

void TransformUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	Vec3 vPos = GetTargetObject()->Transform()->GetRelativePos();
	Vec3 vScale = GetTargetObject()->Transform()->GetRelativeScale();
	Vec3 vRot = GetTargetObject()->Transform()->GetRelativeRotation();
	vRot.ToDegree();

	ImGui::InputFloat3("Relative Position", vPos);
	ImGui::InputFloat3("Relative Scale", vScale);
	ImGui::InputFloat3("Relative Rotation", vRot);

	vRot.ToRadian();
	GetTargetObject()->Transform()->SetRelativePos(vPos);
	GetTargetObject()->Transform()->SetRelativeScale(vScale);
	GetTargetObject()->Transform()->SetRelativeRotation(vRot);
}

