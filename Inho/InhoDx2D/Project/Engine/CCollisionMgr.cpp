#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr() 
    : m_matrix{}
{}

CCollisionMgr::~CCollisionMgr() {}

void CCollisionMgr::tick()
{
    for (UINT iRow = 0; iRow < LAYER_MAX; ++iRow) {
        for (UINT iCol = iRow; iCol < LAYER_MAX; ++iCol) {
            if (!(m_matrix[iRow] & (1 << iCol)))
                continue;
            
            CollisionBtwlayer(iRow, iCol);
        }
    }
}

void CCollisionMgr::CollisionBtwlayer(UINT _left, UINT _right)
{
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
    CLayer* pLeftLayer = pCurLevel->GetLayer(_left);
    CLayer* pRightLayer = pCurLevel->GetLayer(_right);

    const vector<CGameObject*>& vecLeft = pLeftLayer->GetLayerObjects();
    const vector<CGameObject*>& vecRight = pRightLayer->GetLayerObjects();

    for (size_t i = 0; i < vecLeft.size(); ++i) {
        if (nullptr == vecLeft[i]->Collider2D())
            continue;

        size_t j = 0;
        if (_left == _right) {
            j = i + 1;
        }

        for (; j < vecRight.size(); ++j) {
            if (nullptr == vecRight[j]->Collider2D())
                continue;

            CollisionID ID= {};
            ID.LeftID = vecLeft[i]->Collider2D()->GetID();
            ID.RightID = vecRight[i]->Collider2D()->GetID();

            map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
            if (iter == m_mapPrevInfo.end()) {
                m_mapPrevInfo.insert(make_pair(ID.id, false));
                iter = m_mapPrevInfo.find(ID.id);
            }

            bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

            if (CollisionBtwCollider(vecLeft[i]->Collider2D(), vecRight[i]->Collider2D())) {
                if (iter->second) {
                    if (bDead) {
                        vecLeft[i]->Collider2D()->EndOverlap(vecRight[i]->Collider2D());
                        vecRight[i]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
                    }
                    else {
                        vecLeft[i]->Collider2D()->Overlap(vecRight[i]->Collider2D());
                        vecRight[i]->Collider2D()->Overlap(vecLeft[i]->Collider2D());
                    }
                }
                else {
                    if (!bDead) {
                        vecLeft[i]->Collider2D()->BeginOverlap(vecRight[i]->Collider2D());
                        vecRight[i]->Collider2D()->BeginOverlap(vecLeft[i]->Collider2D());
                        iter->second = true;
                    }

                }
            }
            else {
                if (iter->second) {
                    vecLeft[i]->Collider2D()->EndOverlap(vecRight[i]->Collider2D());
                    vecRight[i]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
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

    static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
                              , Vec3(0.5f, 0.5f, 0.f)
                              , Vec3(0.5f, -0.5f, 0.f)
                              , Vec3(-0.5f, -0.5f, 0.f) };

    Vec3 arrProj[4] = {};

    arrProj[0] = XMVector3TransformCoord(arrRect[1], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);
    arrProj[1] = XMVector3TransformCoord(arrRect[3], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);

    arrProj[2] = XMVector3TransformCoord(arrRect[1], matRight) - XMVector3TransformCoord(arrRect[0], matRight);
    arrProj[3] = XMVector3TransformCoord(arrRect[3], matRight) - XMVector3TransformCoord(arrRect[0], matRight);

    Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRight) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeft);

    for (int i = 0; i < 4; i++) {
        Vec3 vProj = arrProj[i];
        vProj.Normalize();

        float ProjAcc = 0.f;

        for (int j = 0; j < 4; j++) {
            ProjAcc += abs(vProj.Dot(arrProj[j]));
        }

        ProjAcc /= 2.f;

        float fCenterDist = abs(vProj.Dot(vCenter));

        if (ProjAcc < fCenterDist) {
            return false;
        }
    }

    return true;
}

void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
    UINT iRow = (UINT)_left;
    UINT iCol = (UINT)_right;

    if (iRow > iCol) {
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
