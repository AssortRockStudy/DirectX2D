#pragma once
#include "CComponent.h"

class CMesh;
class CGraphicsShader;


class CRenderComponent :
    public CComponent
{
private:
    CMesh*              m_Mesh;
    CGraphicsShader*    m_Shader;

public:
    void SetMesh(CMesh* _mesh) { m_Mesh = _mesh; }
    void SetShader(CGraphicsShader* _shader)  { m_Shader = _shader; }

    CMesh* GetMesh() { return m_Mesh; }
    CGraphicsShader* GetShader() { return m_Shader; }

public:
    virtual void finaltick() {};
    virtual void UpdateData() = 0;
    virtual void render() = 0;

public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();

};

