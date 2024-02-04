#pragma once
#include "CAsset.h"

// =======================================
// CShader: 모든 shader가 상속하는 parent class
// =======================================
// - Shader Type: Compute Shader, GraphicsShader

class CShader
	: public CAsset
{
protected:
	ComPtr<ID3DBlob>	m_ErrBlob;

public:
	virtual int UpdatePipeline() = 0;

public:
	CShader(ASSET_TYPE _Type);
	~CShader();
};

