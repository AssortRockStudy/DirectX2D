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

}

void CAssetMgr::init()
{
	CreateDefaultMesh();

	CreateDefaultGraphicsShader();

	CreateDefaultMaterial();
}

void CAssetMgr::CreateDefaultMesh()
{
	CMesh* pMesh = nullptr;

	Vtx arrVtx[4] = {};
	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);;
	arrVtx[1].vColor = Vec4(0.f, 0.f, 1.f, 1.f);;
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(1.f, 0.f, 1.f, 1.f);;
	arrVtx[2].vUV = Vec2(1.f, 1.f);


	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

	//Index Buffer
	//첫번째 삼각형
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;	arrIdx[1] = 1;	arrIdx[2] = 2;

	//두번째 삼각형
	arrIdx[3] = 0;	arrIdx[4] = 2;	arrIdx[5] = 3;

	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh);

	//Topology LineStrip 용도
	//   0(Red)-- 1(Blue)	     
	//    |       |	     
	//   3(G)---- 2(Magenta)   
	arrIdx[0] = 0; arrIdx[1] = 1; arrIdx[2] = 2;
	arrIdx[3] = 3; arrIdx[4] = 0;

	pMesh = new CMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 5);
	AddAsset(L"RectMesh_Debug", pMesh);


	//====================
	//CircleMesh 만들기
	//====================
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	//중심 점
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.5f, 0.5f);

	vecVtx.push_back(v);

	UINT iSlice = 300;
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

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"CircleMesh", pMesh);

	//CircleMesH_Debug
	vecIdx.clear();
	for (size_t i = 0; i < vecVtx.size(); ++i)
	{
		vecIdx.push_back(i);
	}

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh_Debug", pMesh);
	vecVtx.clear();
	vecIdx.clear();

	//==================================
	//CrossMesh만들기
	//==================================
	v.vPos = Vec3(0.f, 0.5f, 0.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.f, -0.5f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, 0.f, 0.f);
	vecVtx.push_back(v);


	v.vPos = Vec3(0.5f, 0.f, 0.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0); vecIdx.push_back(1);
	vecIdx.push_back(2); vecIdx.push_back(3);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CrossMesh", pMesh);
	vecVtx.clear();
	vecIdx.clear();

}

void CAssetMgr::CreateDefaultGraphicsShader()
{
	//====================================
	//Std2dShader 생성
	//====================================
	CGraphicsShader* pShader = nullptr;

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"Std2DShader", pShader);

	//==========================================
	// EffectShader
	//==========================================

	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D_Effect");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::ALPHA_BLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"EffectShader", pShader);

	// =================================
	// GrayFilter Shader
	// Mesh			: RectMesh
	// RS_TYPE		: CULL_BACK
	// DS_TYPE		: NO_TEST_NO_WRITE
	// BS_TYPE		: Default
	// Domain		: DOMAIN_POSTPROCESS
	// =================================
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\postprocess.fx", "VS_GrayFilter");
	pShader->CreatePixelShader(L"shader\\postprocess.fx", "PS_GrayFilter");

	pShader->SetRSType(RS_TYPE::CULL_BACK);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);

	AddAsset(L"GrayFilterShader", pShader);

	//============================================
	// DebugShape Shader
	//=============================================
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\debug.fx", "VS_DebugShape");
	pShader->CreatePixelShader(L"shader\\debug.fx", "PS_DebugShape");

	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	
	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_DEBUG);

	AddAsset(L"DebugShapeShader", pShader);
}

void CAssetMgr::CreateDefaultMaterial()
{
	CMaterial* pMtrl = nullptr;

	// Std2DMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset<CMaterial>(L"Std2DMtrl", pMtrl);

	// BackgroundMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"Std2DShader"));
	AddAsset<CMaterial>(L"BackgroundMtrl", pMtrl);

	//GrayFilterMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"GrayFilterShader"));
	AddAsset<CMaterial>(L"GrayFilterMtrl", pMtrl);

	// DebugShapeMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindAsset<CGraphicsShader>(L"DebugShapeShader"));
	AddAsset<CMaterial>(L"DebugShapeMtrl", pMtrl);

}

Ptr<CTexture> CAssetMgr::CreateTexture(UINT _Width, UINT _Height, DXGI_FORMAT _Format, UINT _Flag, D3D11_USAGE _Usage)
{
	Ptr<CTexture> pTex = new CTexture;

	if (FAILED(pTex->Create(_Width, _Height, _Format, _Flag, _Usage)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"리소스 생성 실패", MB_OK);
		return nullptr;
	}


	return pTex;
}
