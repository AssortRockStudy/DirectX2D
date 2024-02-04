#pragma once
#include "CAsset.h"
#include "CTexture.h"
#include "CGraphicsShader.h"
// =======================================
// CMaterial: GameObject의 graphic 관련 관리
// =======================================
// - GameObject: mesh, matrial 가짐
// - material은 shader를 가짐

class CMaterial :
    public CAsset
{
private:
    FMtrlConst              m_Const;                        // param을 전달해 material을 런타임에 세부적으로 제어할 수 있음
    Ptr<CTexture>           m_arrTex[(UINT)TEX_PARAM::END]; // 한 material이 다양한 texture를 사용할 수도 있음
    Ptr<CGraphicsShader>  m_pShader;

public:
    void UpdatePipeline();

public:
    void SetShader(Ptr<CGraphicsShader> _Shader) { m_pShader = _Shader; }
    void SetTexParam(TEX_PARAM _Param, Ptr <CTexture> _pTex) { m_arrTex[(UINT)_Param] = _pTex; }
    template<typename T>
    void SetScalarParam(SCALAR_PARAM _ParamType, const T& _Value);

    Ptr <CGraphicsShader> GetShader() { return m_pShader; }

public:
    CMaterial();
    ~CMaterial();
};

template<typename T>
void CMaterial::SetScalarParam(SCALAR_PARAM _ParamType, const T& _Value)
{
    const T* val = &_Value;
    switch (_ParamType)
    {
    case SCALAR_PARAM::INT_0:
    case SCALAR_PARAM::INT_1:
    case SCALAR_PARAM::INT_2:
    case SCALAR_PARAM::INT_3:
        m_Const.iArr[(int)_ParamType] = *((int*)val);
        break;

    case SCALAR_PARAM::FLOAT_0:
    case SCALAR_PARAM::FLOAT_1:
    case SCALAR_PARAM::FLOAT_2:
    case SCALAR_PARAM::FLOAT_3:
        m_Const.fArr[(int)_ParamType - (int)SCALAR_PARAM::FLOAT_0] = *((float*)val);
        break;

    case SCALAR_PARAM::VEC2_0:
    case SCALAR_PARAM::VEC2_1:
    case SCALAR_PARAM::VEC2_2:
    case SCALAR_PARAM::VEC2_3:
        m_Const.v2Arr[(int)_ParamType - (int)SCALAR_PARAM::VEC2_0] = *((Vec2*)val);
        break;

    case SCALAR_PARAM::VEC4_0:
    case SCALAR_PARAM::VEC4_1:
    case SCALAR_PARAM::VEC4_2:
    case SCALAR_PARAM::VEC4_3:
        m_Const.v4Arr[(int)_ParamType - (int)SCALAR_PARAM::VEC4_0] = *((Vec4*)val);
        break;

    case SCALAR_PARAM::MAT_0:
    case SCALAR_PARAM::MAT_1:
    case SCALAR_PARAM::MAT_2:
    case SCALAR_PARAM::MAT_3:
        m_Const.matArr[(int)_ParamType - (int)SCALAR_PARAM::MAT_0] = *((Matrix*)val);
        break;
    }
}