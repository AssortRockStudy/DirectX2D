#pragma once
#include "CRenderComponent.h"
// =======================================
// CTilemap: tile ������� Object�� �׸� �� �ְ� �ϴ� Component
// =======================================
// - tile�� ���Ƶ� �ѹ��� �׸� �� ����

class CTileMap :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_Atlas;
    Vec2    m_vTileRenderSize;  // Tile�� render size
    Vec2    m_vTilePixelSize;   // Tile�� origin size
    UINT    m_MapCol;           // TileMap�� col
    UINT    m_MapRow;           // TileMap�� row
    UINT    m_AtlasCol;         // Atlas�� col
    UINT    m_AtlasRow;         // Atlas�� row
    UINT    m_TileIdx;          

public:
    virtual void finaltick() override;
    virtual void render() override;
    virtual void UpdatePipeline() override;

public:
    void SetAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize);
    Ptr<CTexture> GetAtlas() { return m_Atlas; }

public:
    CTileMap();
    ~CTileMap();
};

