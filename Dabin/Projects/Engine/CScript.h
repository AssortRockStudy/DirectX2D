#pragma once
#include "CComponent.h"

// =======================================
// CScript: ��� scprit��  parent class
// =======================================
// - ������ ���� �����δ� Scripts class�� ����� scripts�� �ۼ��� ����

class CScript :
    public CComponent
{
private:
    UINT    m_iScriptType;

public:
    virtual void finaltick() final {}

public:
    CScript();
    ~CScript();
};