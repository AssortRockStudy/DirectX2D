#include "pch.h"
#include "RenderingTest.h"
#include "CDevice.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CMesh.h"
#include "CGraphicsShader.h"

tTransform g_Transform = { Vec4(0.f, 0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f)}; // object transform 값 (constant buffer 전달)

CMesh*	g_RectMesh = nullptr;			// mesh
CMesh*	g_CircleMesh = nullptr;			// mesh

CGraphicsShader* g_Shader = nullptr;	// shader
ComPtr<ID3D11Buffer> g_CB = nullptr;	// constant buffer



int TestInit()
{
	// Vertex Buffer에 vertex 위치 설정
	// - 시계방향
	
	// --------------------------
	// (0) Square
	// --------------------------
	// - NDC좌표계
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
	Vtx v = {Vec3(0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f), Vec2(0.5f, 0.5f)}; // 중심점
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
	// (1) Vertex Buffer 생성
	// --------------------------
	g_RectMesh = new CMesh;
	g_RectMesh->Create(arrVtx, 4, arrIdx, 6);
	g_CircleMesh = new CMesh;
	g_CircleMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());

	// Constant Buffer
	// - object의 이동 위해서 vertex를 직접 update하지 않고, 이동정보(offset), 즉 transform 보냄
	// - vertex shader에서 vector를 해당 값만큼 이동
	D3D11_BUFFER_DESC BuffDesc = {};

	BuffDesc.ByteWidth = sizeof(tTransform);
	BuffDesc.StructureByteStride = sizeof(tTransform);
	BuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CB에 데이터 쓰기 가능
	BuffDesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&BuffDesc, nullptr, g_CB.GetAddressOf())))
	{
		MessageBox(nullptr, L"Failed to Create Constant Buffer", L"TestInit ERROR", MB_OK);
		return E_FAIL;
	}

	// --------------------------
	// (2) Vertex Shader 생성
	// --------------------------
	// (3) Input Layout 생성
	// --------------------------
	g_Shader = new CGraphicsShader;
	g_Shader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	
	// --------------------------
	// (4) Pixel Shader 생성
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
	// - 움직이기 위해 모델 좌표가 아니라 이동 정보를 수정

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

	// System Mem -> GPU Mem, 결정된 최종좌표 이동정보 보냄
	// - Map: GPU의 인터페이스 주소와 연결해둠
	// - Unmap: Map시켜둔 내용이 GPU에 복사됨
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
	CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());	// Pram0: register 등록 (~2^12 byte)
	g_Shader->UpdateData();

	// mesh 선택, draw
	//g_RectMesh->render();
	g_CircleMesh->render();

	// rendering
	CDevice::GetInst()->Present();
}
