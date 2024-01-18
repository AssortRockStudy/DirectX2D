#include "pch.h"
#include "CMeshRender.h"


#include "CMesh.h"
#include "CGraphicsShader.h"

#include "CGameObject.h"
#include "CAnimator2D.h"
#include "CTransform.h"
#include "CMaterial.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::UpdateData()
{
	if ( GetMaterial() != nullptr)
	{
		GetMaterial()->UpdateDate();
	}

	Transform()->UpdateData();
	
}

void CMeshRender::render()
{

	if (GetMesh() == nullptr || GetMaterial() == nullptr)
	{
		return;
	}

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		Animator2D()->Clear();
	}

	UpdateData();

	GetMesh()->Render();
}


