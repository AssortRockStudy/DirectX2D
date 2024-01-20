#pragma once
#include "CEntity.h"

#define GET_GOMPONENT(Type, TYPE) class C##Type* Type(){return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::##TYPE];}

// =======================================
// CGameObject: 모든 GameObject가 상속하는 parent class
// =======================================
class CComponent;
class CRenderComponent;
class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];    // 배열로 관리
    CRenderComponent*       m_RenderCom;                            // render 관리
    vector<CScript*>        m_vecScript;
    vector<CGameObject*>    m_vecChild;
    CGameObject*            m_Parent;
    int                     m_iLayerIdx; // 소속된 Layer Index
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

    // Component type의 반환: 매번 캐스팅해 쓰기 귀찮음
    // 대안1 macro:
    // 대안2 getter: 각 타입마다 함수로 만들어 반환형 만들어줌
    CComponent* GetComponents(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    GET_GOMPONENT(Transform, TRANSFORM);
    GET_GOMPONENT(MeshRender, MESHRENDER);
    GET_GOMPONENT(Camera, CAMERA);
    GET_GOMPONENT(Collider2D, COLLIDER2D);
    GET_GOMPONENT(Animator2D, ANIMATOR2D);
    GET_GOMPONENT(Light2D, LIGHT2D);

public:
    CGameObject();
    ~CGameObject();

    friend class CLayer;
    friend class CTaskMgr;
};

