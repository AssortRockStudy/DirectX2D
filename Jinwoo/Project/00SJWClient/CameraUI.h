#pragma once
#include "ComponentUI.h"

#include <Engine\CGameObject.h>


class CameraUI :
    public ComponentUI
{
private:
    int        m_LayerIdx;

public:
    virtual void render_update() override;

public:
    void SetLayerIdx(int _idx) { m_LayerIdx = _idx; }
    int GetLayerIdx() { return m_LayerIdx; }

public:
    CameraUI();
    ~CameraUI();
};

