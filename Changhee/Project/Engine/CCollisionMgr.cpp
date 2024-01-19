#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < LAYER_MAX; ++iRow)
	{
		for (UINT iCol = iRow; iCol < LAYER_MAX; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			CollisionBtwLayer(iRow, iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(UINT _left, UINT _right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	
	CLayer* pLeftLayer = pCurLevel->GetLayer(_left);
	CLayer* pRightLayer = pCurLevel->GetLayer(_right);

	const vector<CGameObject*>& vecLeft = pLeftLayer->GetLayerObjects();
	const vector<CGameObject*>& vecRight = pRightLayer->GetLayerObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없는 경우
		if (nullptr == vecLeft[i]->Collider2D())
			continue;

		size_t j = 0;
		if (_left == _right) // Left, Right 동일 레이어인 경우, 이중 검사를 피하기 위함
		{
			j = i + 1;
		}

		for (; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->Collider2D())
				continue;

			// 두 충돌체의 아이디를 조합
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->Collider2D()->GetID();
			ID.RightID = vecRight[j]->Collider2D()->GetID();

			// 이전 프레임 충돌 확인
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

			// 현재 프레임 충돌 o
			if (CollisionBtwCollider(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
			{
				// 이전 프레임 충돌 o
				if (iter->second)
				{
					if (bDead)
					{
						vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
						iter->second = false;
					}
					else
					{
						vecLeft[i]->Collider2D()->Overlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->Overlap(vecLeft[i]->Collider2D());
					}
				}
				// 이전 프레임 충돌 x
				else
				{
					// Dead가 아니라면 충돌 처리
					if (!bDead)
					{
						vecLeft[i]->Collider2D()->BeginOverlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->BeginOverlap(vecLeft[i]->Collider2D());
						iter->second = true;
					}
				}
			}
			// 현재 프레임 충돌 x
			else
			{
				// 이전 프레임 충돌 o
				if (iter->second)
				{
					vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight)
{
	const Matrix& matLeft = _pLeft->GetColliderWorldMat();
	const Matrix& matRight = _pRight->GetColliderWorldMat();

	// Rect Local
	// 0 -- 1
	// |    |
	// 3 -- 2

	static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
						  , Vec3(0.5f, 0.5f, 0.f)
						  , Vec3(0.5f, -0.5f, 0.f)
						  , Vec3(-0.5f, -0.5f, 0.f) };

	// 투영 축 구하기
	Vec3 arrProj[4] = {};

	arrProj[0] = XMVector3TransformCoord(arrRect[1], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);

	arrProj[2] = XMVector3TransformCoord(arrRect[1], matRight) - XMVector3TransformCoord(arrRect[0], matRight);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matRight) - XMVector3TransformCoord(arrRect[0], matRight);

	// 중심 사이의 벡터
	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRight) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeft);

	// 구한 축으로 투영 시키기
	for (int i = 0; i < 4; ++i)
	{
		// 투영 시킬 축
		Vec3 vProj = arrProj[i];
		vProj.Normalize();

		// 투영 길이를 더할 변수
		float ProjAcc = 0.f;

		// 4개의 벡터를 각각 투영하여 합한 뒤 절반을 나눔
		for (int j = 0; j < 4; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}
		ProjAcc /= 2.f;

		// 중심을 이은 벡터를 투영축에 투영
		float fCenterDist = abs(vProj.Dot(vCenter));

		// 4개의 벡터의 합이 중심의 투영의 길이보다 작으면 분리축 존재
		if (ProjAcc < fCenterDist)
		{
			return false;
		}
	}

	return true;
}

void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = _left;
	UINT iCol = _right;

	// 행이 더 크도록 정렬
	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::LayerCheck(const wstring& _LeftLayer, const wstring& _RightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLeftLayer = pCurLevel->GetLayer(_LeftLayer);
	CLayer* pRightLayer = pCurLevel->GetLayer(_RightLayer);

	assert(pLeftLayer && pRightLayer);

	LayerCheck(pLeftLayer->GetLayerIdx(), pRightLayer->GetLayerIdx());
}
