#pragma once
#include "CEntity.h"

#define GET_COMPONENT(Type, TYPE) class C##Type* Type(){return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::##TYPE];}

// =======================================
// CGameObject: ��� GameObject�� ����ϴ� parent class
// =======================================
class CComponent;
class CRenderComponent;
class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];    // �迭�� ����
    CRenderComponent*       m_RenderCom;                            // render ����
    vector<CScript*>        m_vecScript;
    vector<CGameObject*>    m_vecChild;
    CGameObject*            m_Parent;
    int                     m_iLayerIdx; // �Ҽӵ� Layer Index
    bool                    m_bDead;

public:
    void begin();
    void tick();
    void finaltick();
    void render();

    void DisconnectWithParent();
    void DisconnectWithLayer();
    void Destroy();

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Child);
    CGameObject* GetParent() { return m_Parent; }
    bool IsDead() { return m_bDead; }
    vector<CGameObject*>& GetChild() { return m_vecChild; }
    const vector<CScript*>& GetScripts() { return m_vecScript; }
    CRenderComponent* GetRenderComponent() { return m_RenderCom; }

    // Component type�� ��ȯ: �Ź� ĳ������ ���� ������
    // ���1 macro:
    // ���2 getter: �� Ÿ�Ը��� �Լ��� ����� ��ȯ�� �������
    CComponent* GetComponents(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(TileMap, TILEMAP);
    GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);

public:
    CGameObject();
    ~CGameObject();

    friend class CLayer;
    friend class CTaskMgr;
};

