#pragma once
#include "UI.h"
#include <Engine/CGameObject.h>
#include <Engine/CAsset.h>

class Inspector :
    public UI
{
private:
    CGameObject* m_TargetObject;
    Ptr<CAsset>     m_TargetAsset;

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    void SetTargetObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset);

public:
    Inspector();
    ~Inspector();
};


// 정보 갖고 있고 값 수정 변경 가능케 하는

// GameObject 정보
//  - 컴포넌트
//  - 스크립트

// Asset 정보
//  - 각 에셋의 정보