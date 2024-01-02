#include "pch.h"
#include "CMaterial.h"

#include "CGraphicsShader.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CTexture.h"


CMaterial::CMaterial()
	:CAsset(ASSET_TYPE::MATERIAL)
	, m_Const{}
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::UpdateData()
{
	if (nullptr == m_pShader.Get())
		return;

	m_pShader->UpdateData();

	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		if (nullptr != m_arrTex[i].Get())
		{
			m_arrTex[i]->UpdateData(i);
			m_Const.bTex[i] = 1;
		}
		else
		{
			CTexture::Clear(i);
			m_Const.bTex[i] = 0;
		}
	}

	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL_CONST);
	pCB->SetData(&m_Const);
	pCB->UpdateData();

	if (nullptr != m_pShader)
	{
		m_pShader->UpdateData();
	}
}


void CMaterial::SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _pTex)
{
	m_arrTex[_Param] = _pTex;
}
