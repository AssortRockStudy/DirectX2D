#pragma once
#include "CEntity.h"

#define GET_GOMPONENT(Type, TYPE) class C##Type* Type(){return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::##TYPE];}

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

public:
    void begin();
    void tick();
    void finaltick();
    void render();
    void DisconnectParent();

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Child);
    // Component type�� ��ȯ: �Ź� ĳ������ ���� ������
    // ���1 macro:
    // ���2 getter: �� Ÿ�Ը��� �Լ��� ����� ��ȯ�� �������
    CComponent* GetGomponents(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CGameObject* GetParent() { return m_Parent; }

    GET_GOMPONENT(Transform, TRANSFORM);
    GET_GOMPONENT(MeshRender, MESHRENDER);
    GET_GOMPONENT(Camera, CAMERA);

public:
    CGameObject();
    ~CGameObject();
};

