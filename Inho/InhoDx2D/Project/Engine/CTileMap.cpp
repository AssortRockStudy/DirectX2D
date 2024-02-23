#include "pch.h"
#include "CTileMap.h"

#include "CAssetMgr.h"
#include "CMesh.h"

#include "CTransform.h"
#include "CStructuredBuffer.h"

CTileMap::CTileMap()
	:CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_FaceX(2)
	, m_FaceY(2)
	, m_vTileRenderSize(Vec2(128.f, 128.f))
	, m_TileIdx(47)
	, m_TileInfoBuffer(nullptr)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));

	m_TileInfoBuffer = new CStructuredBuffer;

	SetFace(m_FaceX, m_FaceY);
}

CTileMap::~CTileMap()
{
	if (nullptr != m_TileInfoBuffer)
		delete m_TileInfoBuffer;
}

void CTileMap::SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize)
{
	m_TileAtlas = _Atlas;
	m_vTilePixelSize = _TilePixelSize;

	m_MaxCol = m_TileAtlas->GetWidth() / (UINT)m_vTilePixelSize.x;
	m_MaxRow = m_TileAtlas->GetHeight() / (UINT)m_vTilePixelSize.y;
}


void CTileMap::finaltick()
{
	Vec3 vTileMapSize = Vec3(m_FaceX * m_vTileRenderSize.x, m_FaceY * m_vTileRenderSize.y, 1.f);
	Transform()->SetRelativeScale(vTileMapSize);
}

void CTileMap::UpdateData()
{
}

void CTileMap::render()
{
	GetMaterial()->SetTexParam(TEX_0, m_TileAtlas);

	GetMaterial()->SetScalarParam(INT_0, m_FaceX);
	GetMaterial()->SetScalarParam(INT_1, m_FaceY);

	GetMaterial()->SetScalarParam(VEC2_0, m_vSliceSizeUV);

	m_TileInfoBuffer->SetData(m_vecTileInfo.data(), m_vecTileInfo.size());

	m_TileInfoBuffer->UpdateData(20);

	GetMaterial()->UpdateData();

	Transform()->UpdateData();

	GetMesh()->render();
}

void CTileMap::SetFace(UINT _FaceX, UINT _FaceY)
{
	m_FaceX = _FaceX;
	m_FaceY = _FaceY;

	vector<tTileInfo> vecTemp;
	m_vecTileInfo.swap(vecTemp);
	m_vecTileInfo.resize(_FaceX * _FaceY);

	m_TileInfoBuffer->Create(sizeof(tTileInfo), _FaceX * _FaceY, SB_TYPE::READ_ONLY, true);
}

void CTileMap::SetTileIndex(UINT _Row, UINT _Col, UINT _ImgIdx)
{
	if (nullptr == m_TileAtlas)
		return;

	UINT idx = _Row * m_FaceX + _Col;

	UINT iRow = _ImgIdx / m_MaxCol;
	UINT iCol = _ImgIdx % m_MaxCol;

	m_vecTileInfo[idx].vLeftTopUV = Vec2((iCol * m_vTilePixelSize.x) / m_TileAtlas->GetWidth()
																				, (iRow * m_vTilePixelSize.y) / m_TileAtlas->GetHeight());
	m_vecTileInfo[idx].bRender = 1;
}