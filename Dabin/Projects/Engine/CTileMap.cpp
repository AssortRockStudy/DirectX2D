#include "pch.h"
#include "CTileMap.h"
#include "CTransform.h"
#include "CAssetMgr.h"
#include "CStructuredBuffer.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_MapCol(1)
	, m_MapRow(1)
	, m_AtlasCol(1)
	, m_AtlasRow(1)
	, m_Atlas(nullptr)
	, m_vTileRenderSize(Vec2(128.f, 128.f))
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMat"));
	m_TileInfoBuffer = new CStructuredBuffer;	// SetMap()에서 TileInfoBuffer Setting하므로 초기화 순서 바꾸면 안 됨
	SetMap(m_MapCol, m_MapRow);
}

CTileMap::~CTileMap()
{
	if (m_TileInfoBuffer)
		delete m_TileInfoBuffer;
}

void CTileMap::finaltick()
{
	Vec3 vTileMapSz = Vec3(m_MapCol * m_vTileRenderSize.x, m_MapRow * m_vTileRenderSize.y, 1.f);
	Transform()->SetRelativeScale(vTileMapSz);
}

void CTileMap::render()
{
	// tile info update: texture const params
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_Atlas);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, m_MapCol);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, m_MapRow);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, m_vSliceSizeUV);

	// tile info update: 
	m_TileInfoBuffer->SetData(m_vecTileInfo.data(), (UINT)m_vecTileInfo.size());
	m_TileInfoBuffer->UpdatePipeline(20);

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
	m_vSliceSizeUV = Vec2(m_vTilePixelSize.x / m_Atlas->GetWidth()
						, m_vTilePixelSize.y / m_Atlas->GetHeight());
}

void CTileMap::SetMap(UINT _Row, UINT _Col)
{
	m_MapRow = _Row;
	m_MapCol = _Col;

	vector<FTileInfo> vecTmp;
	m_vecTileInfo.swap(vecTmp);
	m_vecTileInfo.resize(_Row * _Col);
	m_TileInfoBuffer->Create(sizeof(FTileInfo), _Row * _Col, SB_TYPE::READ_ONLY, true);
}

void CTileMap::SetTileImgIdx(UINT _Row, UINT _Col, UINT _ImgIdx)
{
	if (!m_Atlas.Get())
		return;

	UINT tileIdx = _Row * m_MapCol + _Col;
	UINT iRow = _ImgIdx / m_AtlasCol;
	UINT iCol = _ImgIdx % m_AtlasCol;
	m_vecTileInfo[tileIdx].vLeftTopUV = Vec2((iCol * m_vTilePixelSize.x) / m_Atlas->GetWidth()
										, (iRow * m_vTilePixelSize.y) / m_Atlas->GetHeight());
	m_vecTileInfo[tileIdx].bRender = 1;
}