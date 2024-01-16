#pragma once
#include "CShader.h"

class CGraphicsShader :
    public CShader
{

private:
    ComPtr<ID3DBlob>    m_VSBlob;
    ComPtr<ID3DBlob>    m_HSBlob;
    ComPtr<ID3DBlob>    m_DSBlob;
    ComPtr<ID3DBlob>    m_GSBlob;
    ComPtr<ID3DBlob>    m_PSBlob;

    ComPtr<ID3D11VertexShader>      m_VS;
    ComPtr<ID3D11HullShader>        m_HS;
    ComPtr<ID3D11DomainShader>      m_DS;
    ComPtr<ID3D11GeometryShader>    m_GS;
    ComPtr<ID3D11PixelShader>       m_PS;

    ComPtr<ID3D11InputLayout>       m_Layout;

    D3D11_PRIMITIVE_TOPOLOGY        m_Topology;

    // Rasterizer State
    RS_TYPE                         m_RSType;

    // OutputMerge
    // DepthStencilState
    DS_TYPE                         m_DSType;

    // BlendState
    BS_TYPE                         m_BSType;

public:
    int CreateVertexShader(const wstring& _strRelativePath, const string& _strFuncName);
    int CreateHullShader();
    int CreateDomainShader();
    int CreateGeometryShader();
    int CreatePixelShader(const wstring& _strRelativePath, const string& _strFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { m_Topology = _Topology; }
    D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return m_Topology; }
    void SetRSType(RS_TYPE _Type) { m_RSType = _Type; }
    void SetDSType(DS_TYPE _Type) { m_DSType = _Type; }
    void SetBSType(BS_TYPE _Type) { m_BSType = _Type; }
public:
    virtual void UpdateData();

public:
    CGraphicsShader();
    ~CGraphicsShader();
};

