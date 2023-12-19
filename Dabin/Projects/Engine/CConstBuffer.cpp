#include "pch.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CConstBuffer::CConstBuffer()
	: m_CB{}
	, m_Desc{}
{
}

CConstBuffer::~CConstBuffer()
{
}

int CConstBuffer::Create(UINT _ElementSize, UINT _ElementCount)
{
	m_ElementSize = _ElementSize;
	m_ElementCount = _ElementCount;

	m_Desc = {};
	m_Desc.ByteWidth = m_ElementSize * m_ElementCount;
	m_Desc.StructureByteStride = m_ElementSize;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CB�� ������ ���� ����
	m_Desc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
	{
		MessageBox(nullptr, L"Failed to Create Constant Buffer", L"TestInit ERROR", MB_OK);
		return E_FAIL;
	}
	
	return S_OK;
}

void CConstBuffer::SetData(void* _Src, UINT _ElementCount)
{
	// ����Ʈ �� ����
	if (_ElementCount == 0)
		_ElementCount = m_ElementCount;
	
	// System Mem -> GPU Mem, ������ ������ǥ �̵����� ����
	// - Map: GPU�� �������̽� �ּҿ� �����ص�
	// - Unmap: Map���ѵ� ������ GPU�� �����
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _Src, m_ElementSize *= _ElementCount);
	CONTEXT->Unmap(m_CB.Get(), 0);
}

void CConstBuffer::UpdateData(UINT _RegisterNum)
{
	// ��� shader�� ���
	CONTEXT->VSSetConstantBuffers(_RegisterNum, 1, m_CB.GetAddressOf());	// Pram0: register ��� (~2^12 byte)
	CONTEXT->HSSetConstantBuffers(_RegisterNum, 1, m_CB.GetAddressOf());	// Pram0: register ��� (~2^12 byte)
	CONTEXT->DSSetConstantBuffers(_RegisterNum, 1, m_CB.GetAddressOf());	// Pram0: register ��� (~2^12 byte)
	CONTEXT->GSSetConstantBuffers(_RegisterNum, 1, m_CB.GetAddressOf());	// Pram0: register ��� (~2^12 byte)
	CONTEXT->PSSetConstantBuffers(_RegisterNum, 1, m_CB.GetAddressOf());	// Pram0: register ��� (~2^12 byte)
}
