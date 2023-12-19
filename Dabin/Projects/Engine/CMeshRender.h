#pragma once
#include "CRenderComponent.h"

// =======================================
// CMeshRender: Mesh render ��� ���
// =======================================

class CMeshRender :
    public CRenderComponent
{
public: 
    virtual void render() override;
    virtual void UpdateData() override;

public:
    CMeshRender();
    ~CMeshRender();
};

