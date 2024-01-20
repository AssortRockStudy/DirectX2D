#include "pch.h"
#include "CMaterial.h"
#include "CDevice.h"
#include "CConstBuffer.h"
#include "CGraphicsShader.h"
#include "CTexture.h"

CMaterial::CMaterial()
	: CAsset(ASSET_TYPE::MATERIAL)
	, m_Const{}
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::UpdatePipeline()
{
	if (!m_pShader.Get())
		return;

	// binding Shader
	m_pShader->UpdatePipeline();

	// binding Texture
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		if (m_arrTex[i].Get())
		{
			m_arrTex[i]->UpdatePipeline(i);
			m_Const.bTex[i] = 1;
		}
		else
		{
			CTexture::ClearPipeline(i); // 남아있는 이전 obj의 pipeline data 초기화
			m_Const.bTex[i] = 0;
		}
	}

	// binding Material Const Param
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL_CONST);	// static
	pCB->SetData(&m_Const);
	pCB->UpdatePipeline();
}
