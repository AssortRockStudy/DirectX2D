#pragma once
#include "CComponent.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "Ptr.h"

// =======================================
// CRenderComponent: renderComponents가 상속하는 parent class
// =======================================

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>              m_Mesh;
    Ptr<CMaterial>          m_Mat;

public:
    virtual void finaltick() {};
    virtual void UpdatePipeline() = 0;
    virtual void render() = 0;

public:
    Ptr<CMesh> GetMesh() { return m_Mesh; }
    Ptr<CMaterial> GetMaterial() { return m_Mat; }
    void SetMesh(Ptr<CMesh> _Mesh) { m_Mesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mat) { m_Mat = _Mat; }

public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();
};

