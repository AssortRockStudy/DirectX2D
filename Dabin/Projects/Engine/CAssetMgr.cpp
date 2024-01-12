#include "pch.h"
#include "CAssetMgr.h"
#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CMaterial.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	// Ptr 사용해 refcount 1이 되면 할당 해제하므로 AssetMgr가 종료시 처리하지 않아도 됨
}

void CAssetMgr::CreateDefaultMesh()
{
	CMesh* rectMesh = nullptr;
	CMesh* circleMesh = nullptr;

	// Square
	// Vertex Buffer에 vertex 위치 설정
	// - 시계방향
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
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2;
	arrIdx[3] = 0; arrIdx[4] = 2; arrIdx[5] = 3;

	// Circle
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v = { Vec3(0.f, 0.f, 0.f), Vec4(1.f, 1.f, 1.f, 1.f), Vec2(0.5f, 0.5f) }; // 중심점
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
	rectMesh = new CMesh;
	rectMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", rectMesh);

	circleMesh = new CMesh;
	circleMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh", circleMesh);
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
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);



	// --------------------------
	// Shader 생성
	// --------------------------
	// Std2DShader
	AddAsset(L"Std2DShader", pShader);

	// EffectShader
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ONE_ONE);

	AddAsset(L"EffetShader", pShader);

	// DebugShape Shader
	pShader = new CGraphicsShader();
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugShape");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	AddAsset(L"DebugShapeShader", pShader);
}

void CAssetMgr::CreateDefaultMaterial()
{
	CMaterial* pMat;

	// Std2D Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset(L"Std2DMat", pMat);

	// DebugShape Mat
	pMat = new CMaterial;
	pMat->SetShader(FindAsset<CGraphicsShader>(L"DebugShapeShader"));
	AddAsset(L"DebugShapeMat", pMat);
}

void CAssetMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultGraphicsShader();
	CreateDefaultMaterial();
}