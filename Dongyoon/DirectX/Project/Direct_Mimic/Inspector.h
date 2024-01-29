#pragma once
#include "UI.h"

// GameObject 정보
//  - 컴포넌트
//  - 스크립트
// Asset 정보
//  - 각 에셋의 정보


#include <Engine\CGameObject.h>
#include <Engine\CAsset.h>

class TransformUI;

class Inspector :
	public UI
{
private:
	CGameObject* m_TargetObject;
	Ptr<CAsset>	 m_TargetAsset;

	TransformUI* m_TransformUI;

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

