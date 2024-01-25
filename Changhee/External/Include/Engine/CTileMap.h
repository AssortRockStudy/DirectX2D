#pragma once
#include "CRenderComponent.h"

class CStructuredBuffer;

struct tTileInfo
{
    Vec2    vLeftTopUV;
    int     bRender;
    int     padding;
};


class CTileMap :
    public CRenderComponent
{
private:
    UINT                m_FaceX;
    UINT                m_FaceY;
    Vec2                m_vTileRenderSize;

    Vec3                m_vTileMapWorldPos;

    Ptr<CTexture>       m_TileAtlas;
    Vec2                m_vTilePixelSize;
    Vec2                m_vSliceSizeUV;

    UINT                m_MaxCol;
    UINT                m_MaxRow;

    UINT                m_TileIdx;

    vector<tTileInfo>   m_vecTileInfo;
    CStructuredBuffer*  m_TileInfoBuffer;

public:
    UINT GetFaceX() { return m_FaceX; }
    UINT GetFaceY() { return m_FaceY; }
    Ptr<CTexture> GetTileAtlas() { return m_TileAtlas; }

    void SetFace(UINT _FaceX, UINT _FaceY);
    void SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize);
    void SetTileIndex(UINT _Row, UINT _Col, UINT _ImgIdx);

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;
    virtual void render() override;

public:
    CTileMap();
    ~CTileMap();
};

