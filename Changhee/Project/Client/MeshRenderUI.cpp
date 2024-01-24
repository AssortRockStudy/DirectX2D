#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/CMeshRender.h>

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
	ComponentUI::render_update();



	CGameObject* pTarget = GetTargetObject();
	CMeshRender* pMeshRender = pTarget->MeshRender();

	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	Ptr<CMaterial> pMaterial = pMeshRender->GetMaterial();

	ImGui::Text(ToString(pMesh->GetKey()).c_str());
	ImGui::Text(ToString(pMaterial->GetKey()).c_str());

	string meshname = ToString(pMesh->GetKey()).c_str();
	string mtrlname = ToString(pMaterial->GetKey()).c_str();

	ImGui::Text("Mesh    ");
	ImGui::SameLine();
	ImGui::InputText("##MeshName", (char*)meshname.c_str(), meshname.length(), ImGuiInputTextFlags_ReadOnly);

	ImGui::Text("Material");
	ImGui::SameLine();
	ImGui::InputText("##MtrlName", (char*)mtrlname.c_str(), mtrlname.length(), ImGuiInputTextFlags_ReadOnly);

}
