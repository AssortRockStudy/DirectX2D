#include "pch.h"
#include "Test.h"

#include "CDevice.h"

Vtx g_vtx[3] = {};

ComPtr<ID3D11Buffer> g_VB = nullptr;
ComPtr<ID3D11VertexShader> g_VS = nullptr;
ComPtr<ID3D11PixelShader> g_PS = nullptr;

int TestInit()
{
    // 정점 생성
    g_vtx[0].vPos = Vec3(0.f, 1.f, 0.f);
    g_vtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
    g_vtx[0].vUV = Vec2(0.f, 0.f);

    g_vtx[1].vPos = Vec3(1.f, -1.f, 0.f);
    g_vtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
    g_vtx[1].vUV = Vec2(0.f, 0.f);

    g_vtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
    g_vtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
    g_vtx[2].vUV = Vec2(0.f, 0.f);

    // 정점 버퍼 생성
    D3D11_BUFFER_DESC BufferDesc = {};

    BufferDesc.ByteWidth = sizeof(Vtx) * 3;
    BufferDesc.StructureByteStride = sizeof(Vtx);
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    BufferDesc.CPUAccessFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;

    // g_Vtx 배열의 데이터를 초기 데이터로 설정
    D3D11_SUBRESOURCE_DATA tSubData = {};
    tSubData.pSysMem = g_vtx;

    if (FAILED(DEVICE->CreateBuffer(&BufferDesc, &tSubData, g_VB.GetAddressOf()))) {
        MessageBox(nullptr, L"버텍스 버퍼 생성 실패", L"TestInit 오류", MB_OK);
        return E_FAIL;
    }

    return S_OK;
}

void TestProgress()
{
    float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
    CDevice::GetInst()->ClearRenderTarget(ClearColor);

    UINT iStride = 0;
    UINT iOffset = 0;
    CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
    CONTEXT->VSSetShader(g_VS.Get(), 0, 0);
    CONTEXT->PSSetShader(g_PS.Get(), 0, 0);

    CDevice::GetInst()->Present();

}

void TestRelease()
{
}
