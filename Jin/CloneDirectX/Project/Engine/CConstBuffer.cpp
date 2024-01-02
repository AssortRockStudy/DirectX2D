#include "pch.h"
#include "CConstBuffer.h"

#include "CDevice.h"

CConstBuffer::CConstBuffer(CB_TYPE _Type)
    : m_Desc{}
    , m_Type(_Type)
{
}

CConstBuffer::~CConstBuffer()
{
}


int CConstBuffer::Create(UINT _ElementSize, UINT _ElementCount)
{
    m_ElementSize = _ElementSize;
    m_ElementCount = _ElementCount;

    m_Desc.ByteWidth = m_ElementSize * m_ElementCount;
    m_Desc.StructureByteStride = m_ElementSize;
    m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    m_Desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    m_Desc.Usage = D3D11_USAGE_DYNAMIC;

    if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
    {
        MessageBox(nullptr, L"상수 버퍼 생성 실패", L"TestInit 오류 !! ",MB_OK);
    }
    return S_OK;
}

void CConstBuffer::SetData(void* _Src, UINT _ElementCount)
{
    if (0 == _ElementCount)
    {
        _ElementCount = m_ElementCount;
    }

    D3D11_MAPPED_SUBRESOURCE tSub = {};

    CONTEXT->Map(m_CB.Get(), 0 , D3D11_MAP_WRITE_DISCARD, 0, &tSub);
    memcpy(tSub.pData, _Src, m_ElementSize * _ElementCount);
    CONTEXT->Unmap(m_CB.Get(), 0);
}

void CConstBuffer::UpdateData()
{
    CONTEXT->VSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
    CONTEXT->HSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
    CONTEXT->DSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
    CONTEXT->GSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
    CONTEXT->PSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
}

