#include "pch.h"
#include "Test.h"

#include "CDevice.h"


// �ﰢ�� �׸���
Vtx g_vtx[3] = {};

// ������ �����ϴ� ��������
ComPtr<ID3D11Buffer> g_VB = nullptr;

ComPtr<ID3D11VertexShader> g_VS = nullptr;
ComPtr<ID3D11PixelShader> g_PS = nullptr;


int TestInit()
{
	// ���������� �ﰢ�� ��ġ ����
	g_vtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_vtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	g_vtx[0].vUV = Vec2(0.f, 0.f);

	g_vtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_vtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	g_vtx[1].vUV = Vec2(0.f, 0.f);

	g_vtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_vtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	g_vtx[2].vUV = Vec2(0.f, 0.f);

	// ���ؽ� ���� ����
	D3D11_BUFFER_DESC tBufferDesc = {};
	
	tBufferDesc.ByteWidth = sizeof(Vtx) * 3;
	tBufferDesc.StructureByteStride = sizeof(Vtx);
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	// g_Vtx �迭�� �����͸� �ʱ� �����ͷ� ����
	D3D11_SUBRESOURCE_DATA tSubData = {};
	tSubData.pSysMem = g_vtx;

	// ���ؽ� ���� ����
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSubData, g_VB.GetAddressOf())))
	{
		MessageBox(nullptr, L"���ؽ� ���� ���� ����", L"TestInit ����", MB_OK);
		return E_FAIL;
	}

	return 0;
}

void TestProgress()
{
	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearRenderTarget(ClearColor);

	// �ﰢ�� �׸���
	UINT iStride = 0;
	UINT iOffset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);

	CONTEXT->VSSetShader(g_VS.Get(), 0, 0);
	CONTEXT->PSSetShader(g_PS.Get(), 0, 0);

	CONTEXT->Draw(3, 0);

	CDevice::GetInst()->Present();
}

void TestRelease()
{
}
