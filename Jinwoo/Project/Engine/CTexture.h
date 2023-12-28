#pragma once
#include "CAsset.h"



class CTexture :
    public CAsset
{
private:
    ScratchImage                        m_Image;    // 텍스처 로딩 및 시스템 메모리 관리
    ComPtr<ID3D11Texture2D>             m_Tex2D;    // 텍스처 데이터를 GPU 메모리에 관리
    D3D11_TEXTURE2D_DESC                m_Desc;     // 텍스처 생성 정보

    ComPtr<ID3D11RenderTargetView>      m_RTV;      // 렌더타겟 용도
    ComPtr<ID3D11DepthStencilView>      m_DSV;      // 뎁스 스텐실 용도
    ComPtr<ID3D11ShaderResourceView>    m_SRV;      // 쉐이더에서 사용하는 용도(텍스처 레지스터(t) 바인딩)
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;      // GPGPU(General Purpose GPU) - ComputeShader, 읽기 쓰기 동시가능
                                                    // (Unordered Register(u) 에 바인딩 가능)

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    void UpdateData(int _RegisterNum);

    static void Clear(int _RegisterNum);

public:
    CTexture();
    ~CTexture();

    friend class CAssetMgr;
};

