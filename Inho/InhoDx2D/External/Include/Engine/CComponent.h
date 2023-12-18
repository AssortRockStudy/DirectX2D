#pragma once
#include "CEntity.h"

#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type) C##Type* Type() { return m_Owner->Type(); }

class CGameObject;
class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE m_Type;
    CGameObject* m_Owner;

public:
    virtual void begin() {};
    virtual void tick() {}
    virtual void finaltick() = 0;
    virtual void UpdateData() {}

public:
    COMPONENT_TYPE GetType() { return m_Type; }
    CGameObject* GetOwner() { return m_Owner; }

    GET_OTHER_COMPONENT(Transform);
    GET_OTHER_COMPONENT(MeshRender);

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();

    friend class CGameObject;

};

