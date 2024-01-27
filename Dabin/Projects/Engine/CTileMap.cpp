#include "pch.h"
#include "CTileMap.h"
#include "CTransform.h"
#include "CAssetMgr.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_MapCol(2)
	, m_MapRow(2)
	, m_AtlasCol(1)
	, m_AtlasRow(1)
	, m_Atlas(nullptr)
	, m_TileIdx(47)
	, m_vTileRenderSize(Vec2(128.f, 128.f))
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMat"));
}

CTileMap::~CTileMap()
{
}

void CTileMap::finaltick()
{
	Vec3 vTileMapSz = Vec3(m_MapCol * m_vTileRenderSize.x, m_MapRow * m_vTileRenderSize.y, 1.f);
	Transform()->SetRelativeScale(vTileMapSz);
}

void CTileMap::render()
{
	// material texture·Î atlas Àü´Þ
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_Atlas);
	
	UINT iRow = m_TileIdx / m_AtlasCol;
	UINT iCol = m_TileIdx % m_AtlasCol;
	Vec2 vLeftTopUV = Vec2((iCol * m_vTilePixelSize.x) / m_Atlas->GetWidth()
						, (iRow * m_vTilePixelSize.y) / m_Atlas->GetHeight());
	Vec2 vSliceSzUV = Vec2(m_vTilePixelSize.x / m_Atlas->GetWidth()
						, m_vTilePixelSize.y / m_Atlas->GetHeight());

	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, vLeftTopUV);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_1, vSliceSzUV);
	GetMaterial()->UpdatePipeline();
	Transform()->UpdatePipeline();
	GetMesh()->render();
}

void CTileMap::UpdatePipeline()
{
}

void CTileMap::SetAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize)
{
	m_Atlas = _Atlas;
	m_vTilePixelSize = _TilePixelSize;
	m_AtlasCol = m_Atlas->GetWidth() / (UINT)_TilePixelSize.x;
	m_AtlasRow = m_Atlas->GetHeight() / (UINT)_TilePixelSize.y;
}
