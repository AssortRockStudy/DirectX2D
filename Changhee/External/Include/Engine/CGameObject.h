#pragma once
#include "CEntity.h"

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() { return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::##TYPE]; }

class CComponent;
class CRenderComponent;
class CCamera;
class CCollider2D;
class CAnimator2D;
class CLight2D;

class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;

    vector<CScript*>        m_vecScript;
    vector<CGameObject*>    m_vecChild;

    CGameObject*            m_Parent;

    int                     m_iLayerIdx;        // ¼Ò¼Ó Layer Index

    bool                    m_bDead;

public:
    void begin();
    void tick();
    void finaltick();
    void render();

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    CGameObject* GetParent() { return m_Parent; }
    const vector<CGameObject*>& GetChild() { return m_vecChild; }

    const vector<CScript*>& GetScripts() { return m_vecScript; }
    CRenderComponent* GetRenderComopnent() { return m_RenderCom; }

    int GetLayerIdx() { return m_iLayerIdx; }

    template<typename T>
    T* GetScript()
    {
        for (size_t i = 0; i < m_vecScript.size(); ++i)
        {
            if (dynamic_cast<T*>(m_vecScript[i]))
                return (T*)m_vecScript[i];
        }
        return nullptr;
    }

    int  DisconnectWithParent();
    int  DisconnectWithLayer();

    void AddChild(CGameObject* _Child);
    bool IsDead() { return m_bDead; }

    void Destroy();

public:
    CGameObject();
    ~CGameObject();

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(TileMap, TILEMAP);

    friend class CLayer;
    friend class CTaskMgr;
};

