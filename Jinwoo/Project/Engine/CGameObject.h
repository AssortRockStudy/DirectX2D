#pragma once
#include "CEntity.h"

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() {return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::##TYPE];}

class CComponent;
class CRenderComponent;
class CScript;
class CCamera;
class CCollider2D;
class CLight2D;

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;

    vector<CScript*>        m_vecScript;
    vector<CGameObject*>    m_vecChild;

    CGameObject*            m_Parent;

    int                     m_iLayerIdx;    // 오브젝트가 소속되어있는 레이어의 인덱스

    bool                    m_bDead;

public:
    void begin();
    void tick();
    void finaltick();
    void render();

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Light2D, LIGHT2D);

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Child);
   
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CGameObject* GetParent() { return m_Parent; }

    const vector<CScript*>& GetScripts() { return m_vecScript; }

    template<typename T>
    T* GetScript()
    {
        for (size_t i = 0; i < m_vecScript.size(); ++i)
        {
            if (dynamic_cast<T*>(m_vecScript[i]))
            {
                return (T*)m_vecScript[i];
            }

            return nullptr;
        }
    }

    void DisconnectWithParent();
    void DisconnectWithLayer();

    bool IsDead() { return m_bDead; }

    void Destroy();

public:
    CGameObject();
    ~CGameObject();

    friend class CLayer;
    friend class CTaskMgr;
};

