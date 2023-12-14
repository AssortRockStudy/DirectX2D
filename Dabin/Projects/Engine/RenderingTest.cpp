#include "pch.h"
#include "RenderingTest.h"
#include "CDevice.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CMesh.h"
#include "CGraphicsShader.h"

tTransform g_Transform = { Vec4(0.f, 0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f)}; // object transform �� (constant buffer ����)

CMesh*	g_RectMesh = nullptr;			// mesh
CMesh*	g_CircleMesh = nullptr;			// mesh

CGraphicsShader* g_Shader = nullptr;	// shader
ComPtr<ID3D11Buffer> g_CB = nullptr;	// constant buffer



int TestInit()
{
	// Vertex Buffer�� vertex ��ġ ����
	// - �ð����
	
	// --------------------------
	// (0) Square
	// --------------------------
	// - NDC��ǥ��
	//   0(Red)-- 1(Blue)	     
	//    |   \   |	     
	//   3(G)---- 2(Magenta)
	Vtx		arrVtx[4] = {};
	UINT	arrIdx[6] = {};

	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[1].vUV = Vec2(0.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(0.f, 0.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 0.f);

	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2;
	arrIdx[3] = 0; arrIdx[4] = 2; arrIdx[5] = 3;

	// --------------------------
	// (0) Circle
	// --------------------------
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v = {Vec3(0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f), Vec2(0.5f, 0.5f)}; // �߽���
	vecVtx.push_back(v);

	UINT iSlice = 40;
	float fTheta = 0.f;
	float fRadius = 0.5f;

	for (UINT i = 0; i <= iSlice; ++i)
	{
		fTheta = (XM_2PI / iSlice) * i;

		v.vPos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		v.vUV = Vec2(0.f, 0.f);

		vecVtx.push_back(v);
	}

	for (UINT i = 0; i < iSlice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// --------------------------
	// (1) Vertex Buffer ����
	// --------------------------
	g_RectMesh = new CMesh;
	g_RectMesh->Create(arrVtx, 4, arrIdx, 6);
	g_CircleMesh = new CMesh;
	g_CircleMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());

	// Constant Buffer
	// - object�� �̵� ���ؼ� vertex�� ���� update���� �ʰ�, �̵�����(offset), �� transform ����
	// - vertex shader���� vector�� �ش� ����ŭ �̵�
	D3D11_BUFFER_DESC BuffDesc = {};

	BuffDesc.ByteWidth = sizeof(tTransform);
	BuffDesc.StructureByteStride = sizeof(tTransform);
	BuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CB�� ������ ���� ����
	BuffDesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&BuffDesc, nullptr, g_CB.GetAddressOf())))
	{
		MessageBox(nullptr, L"Failed to Create Constant Buffer", L"TestInit ERROR", MB_OK);
		return E_FAIL;
	}

	// --------------------------
	// (2) Vertex Shader ����
	// --------------------------
	// (3) Input Layout ����
	// --------------------------
	g_Shader = new CGraphicsShader;
	g_Shader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	
	// --------------------------
	// (4) Pixel Shader ����
	// --------------------------
	g_Shader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	return S_OK;
}

void TestProgress()
{
	Tick();
	Render();
}

void TestRelease()
{
	if (g_RectMesh)
		delete g_RectMesh;

	if (g_CircleMesh)
		delete g_CircleMesh;

	delete g_Shader;
}

void Tick()
{
	// object move
	// - �����̱� ���� �� ��ǥ�� �ƴ϶� �̵� ������ ����

	if (KEY_PRESSED(KEY::A))
	{
		g_Transform.vWorldPos.x -= DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		g_Transform.vWorldPos.x += DT;
	}

	if (KEY_PRESSED(KEY::W))
	{
		g_Transform.vWorldPos.y += DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		g_Transform.vWorldPos.y -= DT;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		g_Transform.vWorldScale += DT * Vec4(1.f, 1.f, 1.f, 1.f);
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		g_Transform.vWorldScale -= DT * Vec4(1.f, 1.f, 1.f, 1.f);
	}

	// System Mem -> GPU Mem, ������ ������ǥ �̵����� ����
	// - Map: GPU�� �������̽� �ּҿ� �����ص�
	// - Unmap: Map���ѵ� ������ GPU�� �����
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, sizeof(tTransform));
	CONTEXT->Unmap(g_CB.Get(), 0);
}

void Render()
{
	// buffer init
	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearRenderTarget(ClearColor);

	// shader setting
	CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());	// Pram0: register ��� (~2^12 byte)
	g_Shader->UpdateData();

	// mesh ����, draw
	//g_RectMesh->render();
	g_CircleMesh->render();

	// rendering
	CDevice::GetInst()->Present();
}
