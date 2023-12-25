#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
private:
    ScratchImage m_Image;
    ComPtr<ID3D11Texture2D> m_Tex2D;
    D3D11_TEXTURE2D_DESC m_Desc;

    ComPtr<ID3D11RenderTargetView> m_RTV;
    ComPtr<ID3D11DepthStencilView> m_DSV;
    ComPtr<ID3D11ShaderResourceView> m_SRV;
    ComPtr<ID3D11UnorderedAccessView> m_UAV;

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    void UpdateData(int _RegisterNum);

public:
    CTexture();
    ~CTexture();
};

