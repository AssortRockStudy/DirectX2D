#include "pch.h"
#include "CSetColorShader.h"

CSetColorShader::CSetColorShader()
	: CComputeShader(1, 1, 1)
{
}

CSetColorShader::~CSetColorShader()
{
}

void CSetColorShader::UpdateData()
{
	m_Const.v4Arr[0] = m_Color;
}

void CSetColorShader::Clear()
{
}
