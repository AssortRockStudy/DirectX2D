#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

enum class LEVEL_STATE
{
    PLAY,
    PAUSE,
    STOP,
};

class CLevel :
    public CEntity
{
private:
    CLayer*     m_arrLayer[LAYER_MAX];

public:
    void begin();
    void tick();
    void finaltick();

    void clear();

public:
    void AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove = true);
    void AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove = true);

    CLayer* GetLayer(int _iLayerIdx) { return m_arrLayer[_iLayerIdx]; }
    CLayer* GetLayer(const wstring& _strLayerName);

    CGameObject* FindObjectByName(const wstring& _strName);
    void FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _vecObj);

public:
    CLevel();
    ~CLevel();

    friend class CLevelMgr;
};

