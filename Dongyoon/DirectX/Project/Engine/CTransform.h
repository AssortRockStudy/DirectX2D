#pragma once
#include "pch.h"
#include "CComponent.h"


class CTransform :
    public CComponent
{
private:
    Vec3 m_vRelativePos;        // ��ġ
    Vec3 m_vRelativeScale;      // ũ��
    Vec3 m_vRelativeRotation;   // ȸ����
    Vec3 m_arrDir[3];           // ��ü�� ���� ����   Ringt, Up, Front


    Matrix m_matWorld;          // ��ü�� ���� ���

public:
    void SetRelativePos(Vec3 _Pos) { m_vRelativePos = _Pos; }
    void SetRelativeScale(Vec3 _Scale) { m_vRelativeScale = _Scale; }
    void SetRelativeRotation(Vec3 _Rotation) { m_vRelativeRotation = _Rotation; }

    Vec3 GetRelativePos() { return  m_vRelativePos; }
    Vec3 GetRelativeScale() { return  m_vRelativeScale; }
    Vec3 GetRelativeRotation() { return  m_vRelativeRotation; }

    const Matrix& GetWorldMat() { return m_matWorld; }

    Vec3 GetDIR(DIR_TYPE _type) { return m_arrDir[(UINT)_type]; }

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;
   
public:
    CTransform();
    ~CTransform();
};
