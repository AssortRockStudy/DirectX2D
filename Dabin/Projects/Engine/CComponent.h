#pragma once
#include "CEntity.h"
#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type) class C##Type* Type() {return m_Owner->Type();}

// =======================================
// CComponent: 모든 component가 상속하는 기본 class
// =======================================
// - Component 기반 설계

class CGameObject;

class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE    m_Type;
    CGameObject*            m_Owner;

public:
    virtual void begin() {};
    virtual void tick() {};
    virtual void finaltick() = 0;
    virtual void UpdatePipeline() {};

public:
    COMPONENT_TYPE GetType() { return m_Type; }
    CGameObject* GetOwner() { return m_Owner; }
    GET_OTHER_COMPONENT(Transform);
    GET_OTHER_COMPONENT(MeshRender);
    GET_OTHER_COMPONENT(Camera);
    GET_OTHER_COMPONENT(Collider2D);
    GET_OTHER_COMPONENT(Animator2D);
    GET_OTHER_COMPONENT(Light2D);
    GET_OTHER_COMPONENT(TileMap);

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();

    friend class CGameObject;
};

