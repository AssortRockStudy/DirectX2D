#include "pch.h"
#include "Collider2DUI.h"

#include <Engine\CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::render_update()
{
	ComponentUI::render_update();

	Vec2 vPos = GetTargetObject()->Collider2D()->GetOffsetPos();
	Vec2 vScale = GetTargetObject()->Collider2D()->GetOffsetScale();
	static int ColType = int(GetTargetObject()->Collider2D()->GetType());
	static bool linkScale = true;

	ImGui::Text("Position");
	ImGui::SameLine(0, 20);	ImGui::PushItemWidth(80);
	ImGui::Text("x"); ImGui::SameLine(); ImGui::DragFloat("##Posx", &vPos.x); ImGui::SameLine();
	ImGui::Text("y"); ImGui::SameLine(); ImGui::DragFloat("##Posy", &vPos.y);

	ImGui::Text("Scale");
	ImGui::SameLine(0, 41);	ImGui::PushItemWidth(80);
	ImGui::Text("x"); ImGui::SameLine(); ImGui::DragFloat("##Scalex", &vScale.x); ImGui::SameLine();
	ImGui::Text("y"); ImGui::SameLine(); ImGui::DragFloat("##Scaley", &vScale.y);
	ImGui::SameLine(); ImGui::Checkbox("Link Scale", &linkScale);

	if (linkScale)
	{
		vScale.y = vScale.x;
	}

	ImGui::Text("Type");
	ImGui::SameLine(0, 63); ImGui::PushItemWidth(80);
	ImGui::Combo("##ColType", &ColType, "RECT\0CIRCLE\0\0");

	GetTargetObject()->Collider2D()->SetOffsetPos(vPos);
	GetTargetObject()->Collider2D()->SetOffsetScale(vScale);
	GetTargetObject()->Collider2D()->SetColliderType((COLLIDER2D_TYPE)ColType);

	// Absolute 체크
	bool bAbsolute = GetTargetObject()->Collider2D()->IsAbsolute();
	ImGui::Text("Scale Absolute");
	ImGui::SameLine();
	ImGui::Checkbox("##Collider2DAbsolute", &bAbsolute);
	GetTargetObject()->Collider2D()->SetAbsolute(bAbsolute);
}