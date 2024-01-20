#pragma once
#include "singleton.h"
// =======================================
// CCollisionMgr: Collision ����, Event ���� �� ���� 
// =======================================

class CCollider2D;

union CollisionID
{
    struct
    {
        UINT LeftID;
        UINT RightID;
    };
    UINT_PTR id;
};

class CCollisionMgr :
    public CSingleton<CCollisionMgr>
{
    SINGLE(CCollisionMgr)

private:
    UINT                    m_matrix[LAYER_MAX];
    map<UINT_PTR, bool>     m_mapPrevInfo;  // ���� ������ �浹���� ���

public:
    void tick();

public:
    void LayerCheck(UINT _left, UINT _right);
    void LayerCheck(const wstring& _LeftLayer, const wstring& _RightLayer);
    void Clear();

private:
    void CollisionBtwLayer(UINT _left, UINT _right);
    bool CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight);
};

