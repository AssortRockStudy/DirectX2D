#pragma once
#include "CAsset.h"
// =======================================
// CTexture: 이미지 리소스 텍스쳐로 생성 및 관리
// =======================================

class CTexture :
    public CAsset
{
private:
    ScratchImage                        m_Image;    // System memory
    ComPtr<ID3D11Texture2D>             m_Tex2D;    // GPU memory
    D3D11_TEXTURE2D_DESC                m_Desc;     // 텍스쳐 생성정보

    ComPtr<ID3D11RenderTargetView>      m_RTV;
    ComPtr<ID3D11DepthStencilView>      m_DSV;
    ComPtr<ID3D11ShaderResourceView>    m_SRV;      // texture register(t) - for Shader
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;      // GPGPU(General Purpose GPU) - for ComputeShader

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    void UpdatePipeline(int _registerNum);
    static void ClearPipeline(int _registerNum);

    UINT GetWidth() { return m_Desc.Width; }
    UINT GetHeight() { return m_Desc.Height; }

public:
    CTexture();
    ~CTexture();
    friend class CAssetMgr;
};