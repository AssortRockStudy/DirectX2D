#include "pch.h"
#include "CAssetMgr.h"

void CAssetMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultGraphicsShader();
	CreateDefaultComputeShader();
	CreateDefaultMaterial();
}

void CAssetMgr::CreateDefaultMesh()
{
	CMesh* pMesh = nullptr;

	// Point
	Vtx vPoint;
	UINT Idx = 0;
	pMesh = new CMesh;
	pMesh->Create(&vPoint, 1, &Idx, 1);
	AddAsset(L"PointMesh", pMesh);

	// Rectangle
	// Vertex Buffer에 vertex 위치 설정
	// - 시계방향
	// - NDC좌표계
	//   0(Red)-- 1(Blue)	     
	//    |   \   |	     
	//   3(G)---- 2(Magenta)
	Vtx		arrVtx[4] = {};
	UINT	arrIdx[6] = {};

	// 길이 1짜리를 만들어주기 위해서 0.5로 잡음
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2;
	arrIdx[3] = 0; arrIdx[4] = 2; arrIdx[5] = 3;

	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6); // (1) Vertex Buffer 생성
	AddAsset(L"RectMesh", pMesh);

	// RectMesh_Debug
	for (int i = 0; i < 4; i++)
		arrIdx[i] = i;
	arrIdx[4] = 0;

	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	AddAsset(L"RectMesh_Debug", pMesh);

	// Circle
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx vtx = { Vec3(0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f), Vec2(0.5f, 0.5f) }; // 중심점
	vecVtx.push_back(vtx);

	UINT iSlice = 40;
	float fTheta = 0.f;
	float fRadius = 0.5f;

	for (UINT i = 0; i <= iSlice; ++i)
	{
		fTheta = (XM_2PI / iSlice) * i;

		vtx.vPos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
		vtx.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vtx.vUV = Vec2(0.f, 0.f);

		vecVtx.push_back(vtx);
	}

	for (UINT i = 0; i < iSlice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh", pMesh);

	// CircleMesh_Debug
	vecIdx.clear();
	for (int i = 1; i < vecVtx.size(); i++)
		vecIdx.push_back(i);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh_Debug", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// CrossMesh
	vtx.vPos = Vec3(0.f, 0.5f, 0.f);
	vtx.vUV = Vec2();
	vtx.vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	vecVtx.push_back(vtx);
	vtx.vPos = Vec3(0.f, -0.5f, 0.f); vecVtx.push_back(vtx);
	vtx.vPos = Vec3(-0.5f, 0.f, 0.f); vecVtx.push_back(vtx);
	vtx.vPos = Vec3(0.5f, 0.f, 0.f); vecVtx.push_back(vtx);

	for (int i = 0; i < 4; ++i)
		vecIdx.push_back(i);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), 4, vecIdx.data(), 4);
	AddAsset(L"CrossMesh_Debug", pMesh);
	vecVtx.clear();
	vecIdx.clear();
}

void CAssetMgr::CreateDefaultGraphicsShader()
{
	CGraphicsShader* pShader = nullptr;

	// shader 생성 위한, pipeline buffer 생성

	// --------------------------
	// (2) Vertex Shader 생성
	// --------------------------
	// (3) Input Layout 생성
	// --------------------------
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");

	// --------------------------
	// (4) Pixel Shader 생성
	// --------------------------
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	// --------------------------
	// Rasterizer, DepthStencil, Blend State
	// --------------------------
	// - Defualt로 선택되는 옵션들 추가 구현
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);



	// --------------------------
	// Shader 생성
	// --------------------------
	// Std2D Shader
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);
	AddAsset(L"Std2DShader", pShader);

	// Effect Shader
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_Effect");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"EffetShader", pShader);

	// TileMap Shader
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\tilemap.fx", "VS_TileMap");
	pShader->CreatePixelShader(L"shader\\tilemap.fx", "PS_TileMap");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"TileMapShader", pShader);

	// Particle Shader
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\particle.fx", "VS_Particle");
	pShader->CreateGeometryShader(L"shader\\particle.fx", "GS_Particle");
	pShader->CreatePixelShader(L"shader\\particle.fx", "PS_Particle");
	
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"ParticleRenderShader", pShader);

	// PostProcess Shader - GrayFilter
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_GrayFilter");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_GrayFilter");
	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);

	AddAsset(L"GrayFilterShader", pShader);

	// PostProcess Shader - Distortion
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_Distortion");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_Distortion");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);

	AddAsset(L"DistortionShader", pShader);

	// UI Shader
	pShader = new CGraphicsShader();
	pShader->CreateVertexShader(L"shader\\UI.fx", "VS_UI");
	pShader->CreatePixelShader(L"shader\\UI.fx", "PS_UI");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"UIShader", pShader);

	// DebugShape Shader
	pShader = new CGraphicsShader();
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugShape");
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugShapeShader", pShader);
}

#include "CSetColorShader.h"
#include "CParticleUpdate.h"
void CAssetMgr::CreateDefaultComputeShader()
{
	Ptr<CComputeShader> pShader = nullptr;

	// SetColorShader
	pShader = new CSetColorShader;
	AddAsset(L"SetColorShader", pShader.Get());

	// SetColorShader
	pShader = new CParticleUpdate;
	AddAsset(L"ParticleUpdateShader", pShader.Get());
}

void CAssetMgr::CreateDefaultMaterial()
{
	CMaterial* pMat;

	// Std2D Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset(L"Std2DMat", pMat);

	// Particle Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"ParticleRenderShader"));
	AddAsset(L"ParticleMat", pMat);

	// Background Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset(L"BackgroundMat", pMat);

	// TileMap Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"TileMapShader"));
	AddAsset(L"TileMapMat", pMat);

	// PostProcess Mat - GrayFilter
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"GrayFilterShader"));
	AddAsset(L"GrayFilterMat", pMat);

	// PostProcess Mat - Distortion
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"DistortionShader"));
	AddAsset(L"DistortionMat", pMat);

	// UI Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"UIShader"));
	AddAsset(L"UIMat", pMat);

	// DebugShape Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"DebugShapeShader"));
	AddAsset(L"DebugShapeMat", pMat);
}