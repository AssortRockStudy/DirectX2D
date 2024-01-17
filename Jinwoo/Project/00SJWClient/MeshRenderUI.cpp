#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine\CMeshRender.h>

MeshRenderUI::MeshRenderUI()
	: ComponentUI("MeshRender", "##MeshRender", COMPONENT_TYPE::MESHRENDER)
{
	SetSize(ImVec2(0.f, 100.f));
	SetComponentTitle("MeshRender");
}

MeshRenderUI::~MeshRenderUI()
{
}

void MeshRenderUI::render_update()
{
	if (nullptr == GetTargetObject())
	{
		return;
	}

	ComponentUI::render_update();

	CGameObject* pTarget = GetTargetObject();
	CMeshRender* pMeshRender = pTarget->MeshRender();

	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	Ptr<CMaterial> pMtrl = pMeshRender->GetMaterial();

	string meshName = ToString(pMesh->GetKey()).c_str();
	string mtrlName = ToString(pMtrl->GetKey()).c_str();

	ImGui::Text("Mesh");
	ImGui::SameLine(0, 46);
	ImGui::SetNextItemWidth(100);
	ImGui::InputText("##MeshName", (char*)meshName.c_str(), meshName.length(), ImGuiInputTextFlags_ReadOnly);

	ImGui::Text("Material");
	ImGui::SameLine(0, 18);
	ImGui::SetNextItemWidth(100);
	ImGui::InputText("##Material", (char*)mtrlName.c_str(), mtrlName.length(), ImGuiInputTextFlags_ReadOnly);
}