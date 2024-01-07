#include "pch.h"
#include "CMeshRender.h"
#include "CMesh.h"
#include "CGraphicsShader.h"
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
	if (GetMesh() == nullptr || GetShader() == nullptr)
		return;

	UpdateData();
	GetMesh()->render();
}

void CMeshRender::UpdateData()
{
	if (GetShader())
		GetShader()->UpdatePipeline();

	GetOwner()->Transform()->UpdateData();
}
