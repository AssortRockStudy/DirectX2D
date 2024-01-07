#pragma once
#include "CAsset.h"

class CGraphicsShader;
class CTexture;

class CMaterial :
    public CAsset
{
private:
    tMtrlConst              m_Const;
    CTexture*               m_arrTex[(UINT)TEX_PARAM::END];

    CGraphicsShader*        m_Shader;

public:
    void SetShader(CGraphicsShader* _Shader) { m_Shader = _Shader; }
    CGraphicsShader* GetShader() { return m_Shader; }

    void UpdateData();

public:
    CMaterial();
    ~CMaterial();
};

