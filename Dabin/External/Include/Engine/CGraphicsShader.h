#pragma once
#include "CShader.h"

// =======================================
// CGraphicsShader: Graphic Pipeline Shader 관리
// =======================================

class CGraphicsShader :
    public CShader
{
private:
    ComPtr<ID3DBlob> m_VSBlob;
    ComPtr<ID3DBlob> m_HSBlob;
    ComPtr<ID3DBlob> m_DSBlob;
    ComPtr<ID3DBlob> m_GSBlob;
    ComPtr<ID3DBlob> m_PSBlob;
    
    ComPtr<ID3D11VertexShader>  m_VS;
    ComPtr<ID3D11HullShader>    m_HS;
    ComPtr<ID3D11DomainShader>  m_DS;
    ComPtr<ID3D11GeometryShader>m_GS;
    ComPtr<ID3D11PixelShader>   m_PS;
    
    ComPtr<ID3D11InputLayout>   m_Layout;	// Input Layout: vertex의 구조 알림
    D3D11_PRIMITIVE_TOPOLOGY    m_Topology;

    RS_TYPE         m_RasterizerType;   // Restarizer State
    
    // OM
    DS_TYPE         m_DSType;   // DepthStencil State
    BS_TYPE         m_BlendType;   // Blend State

    // Shader Domain
    SHADER_DOMAIN   m_Domain;

public:
    virtual int UpdatePipeline();

    int CreateVertexShader(const wstring& _strRelativePath, const string& _strFuncName);
    int CreateHullShader();
    int CreateDomainShader();
    int CreateGeometryShader(const wstring& _strRelativePath, const string& _strFuncName);
    int CreatePixelShader(const wstring& _strRelativePath, const string& _strFuncName);

public:
    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { m_Topology = _Topology; }
    void SetRSType(RS_TYPE _Type) { m_RasterizerType = _Type; }
    void SetDSType(DS_TYPE _Type) { m_DSType = _Type; }
    void SetBSType(BS_TYPE _Type) { m_BlendType = _Type; }
    void SetDomain(SHADER_DOMAIN _domain) { m_Domain = _domain; }
    D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return m_Topology; }
    SHADER_DOMAIN GetDomain() { return m_Domain; }

public:
    CGraphicsShader();
    ~CGraphicsShader();
};