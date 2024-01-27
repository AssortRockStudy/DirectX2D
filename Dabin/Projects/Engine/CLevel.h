#pragma once
#include "CEntity.h"

// =======================================
// CLevel: GameObject가 배치되는 Scene
// =======================================
class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer* m_arrLayer[LAYER_MAX];

private:
    void clear();

public:
    void begin();
    void tick();
    void finaltick();

public:
    void AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove = true);
    void AddObject(CGameObject* _Object, const wstring& _LayerName, bool _bChildMove = true);
    CLayer* GetLayer(int _iLayerIdx) { return m_arrLayer[_iLayerIdx]; }
    CLayer* GetLayer(const wstring& _strLayerName);
    CGameObject* FindObjectByName(const wstring& _strName);
    void FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _out);

public:
    CLevel();
    ~CLevel();

    friend class CLevelMgr;
};

