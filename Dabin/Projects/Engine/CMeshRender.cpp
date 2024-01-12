#include "pch.h"
#include "CMeshRender.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CGameObject.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::render()
{
	if (GetMesh() == nullptr || GetMaterial() == nullptr)
		return;

	UpdatePipeline();
	GetMesh()->render();
}

void CMeshRender::UpdatePipeline()
{
	if (GetMaterial().Get())
		GetMaterial()->UpdatePipeline();

	GetOwner()->Transform()->UpdatePipeline();
}
