#pragma once
#include "CRenderComponent.h"
// =======================================
// CTilemap: tile 기반으로 Object를 그릴 수 있게 하는 Component
// =======================================
// - tile이 많아도 한번에 그릴 수 있음

class CTileMap :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_Atlas;
    Vec2    m_vTileRenderSize;  // Tile의 render size
    Vec2    m_vTilePixelSize;   // Tile의 origin size
    UINT    m_MapCol;           // TileMap의 col
    UINT    m_MapRow;           // TileMap의 row
    UINT    m_AtlasCol;         // Atlas의 col
    UINT    m_AtlasRow;         // Atlas의 row
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

