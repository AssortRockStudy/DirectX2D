#include "pch.h"
#include "UIMeshRender.h"
#include "UIInspectorPannel.h"
#include "UIListPannel.h"
#include "CImGuiMgr.h"
#include "Engine/CMeshRender.h"
#include "Engine/CAssetMgr.h"
#include "Engine/CMesh.h"

UIMeshRender::UIMeshRender()
	: UIComponent("MeshRender", "##MeshRender", COMPONENT_TYPE::MESHRENDER)
{
}

UIMeshRender::~UIMeshRender()
{
}

void UIMeshRender::render_update()
{
	CGameObject* pTarget = GetInspector()->GetTargetObject();
	CMeshRender* pMeshRender = pTarget->MeshRender();

	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	Ptr<CMaterial> pMat = pMeshRender->GetMaterial();
	string meshname = wstrToStr(pMesh->GetKey()).c_str();
	string mtrlname = wstrToStr(pMat->GetKey()).c_str();

	ImGui::Text("Mesh    "); ImGui::SameLine();
	ImGui::InputText("##MeshName", (char*)meshname.c_str(), meshname.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("##MeshBtn", ImVec2(20, 20)))
	{
		UIListPannel* pList = (UIListPannel*)CImGuiMgr::GetInst()->FindUI("##List");
		vector<string> vecMeshName;
		CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::MESH, vecMeshName);

		pList->SetModal(true);
		pList->AddString(vecMeshName);
		//pList->SetDBClickCallback(::MeshSelect);
		pList->SetDBClickeDelegate(this, (DELEGATE_1)&UIMeshRender::MeshSelect);
		pList->Activate();
	}

	ImGui::Text("Material"); ImGui::SameLine();
	ImGui::InputText("##MatName", (char*)mtrlname.c_str(), mtrlname.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("##MatBtn", ImVec2(20, 20)))
	{
		UIListPannel* pList = (UIListPannel*)CImGuiMgr::GetInst()->FindUI("##List");
		vector<string> vecMatName;
		CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::MATERIAL, vecMatName);

		pList->SetModal(true);
		pList->AddString(vecMatName);
		pList->SetDBClickeDelegate(this, (DELEGATE_1)&UIMeshRender::MaterialSelect);
		pList->Activate();
	}
}

void UIMeshRender::MeshSelect(DWORD_PTR _ptr)
{
	wstring strMeshName = str2Wstr((char*)_ptr);
	Ptr<CMesh> pMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(strMeshName);

	GetInspector()->GetTargetObject()->MeshRender()->SetMesh(pMesh);
}

void UIMeshRender::MaterialSelect(DWORD_PTR _ptr)
{
	wstring strMatName = str2Wstr((char*)_ptr);
	Ptr<CMaterial> pMat = CAssetMgr::GetInst()->FindAsset<CMaterial>(strMatName);

	GetInspector()->GetTargetObject()->MeshRender()->SetMaterial(pMat);
}

void MeshSelect(DWORD_PTR _ptr)
{
	wstring strMeshName = str2Wstr((char*)_ptr);
	Ptr<CMesh> pMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(strMeshName);
	
	CGameObject* pTarget = ((UIInspectorPannel*)CImGuiMgr::GetInst()->FindUI("##Inspector"))->GetTargetObject();
	pTarget->MeshRender()->SetMesh(pMesh);
}

void MaterialSelect(DWORD_PTR _ptr)
{
	wstring strMatName = str2Wstr((char*)_ptr);
	Ptr<CMaterial> pMat = CAssetMgr::GetInst()->FindAsset<CMaterial>(strMatName);

	CGameObject* pTarget = ((UIInspectorPannel*)CImGuiMgr::GetInst()->FindUI("##Inspector"))->GetTargetObject();
	pTarget->MeshRender()->SetMaterial(pMat);
}
