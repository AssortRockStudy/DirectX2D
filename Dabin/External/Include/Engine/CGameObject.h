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

public:
    void begin();
    void tick();
    void finaltick();
    void render();
    void DisconnectParent();

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Child);
    // Component type의 반환: 매번 캐스팅해 쓰기 귀찮음
    // 대안1 macro:
    // 대안2 getter: 각 타입마다 함수로 만들어 반환형 만들어줌
    CComponent* GetGomponents(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CGameObject* GetParent() { return m_Parent; }

    GET_GOMPONENT(Transform, TRANSFORM);
    GET_GOMPONENT(MeshRender, MESHRENDER);
    GET_GOMPONENT(Camera, CAMERA);

public:
    CGameObject();
    ~CGameObject();
};

