#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
	: m_eReg(CBV_REGISTER::END)
{
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Create(CBV_REGISTER eReg, uint32 iSize)
{
	m_eReg = eReg;

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = iSize;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, m_pBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void ConstantBuffer::Mapping()
{
	CONTEXT->VSSetConstantBuffers(static_cast<uint8>(m_eReg), 1, m_pBuffer.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(static_cast<uint8>(m_eReg), 1, m_pBuffer.GetAddressOf());
	CONTEXT->GSSetConstantBuffers(static_cast<uint8>(m_eReg), 1, m_pBuffer.GetAddressOf());
	CONTEXT->CSSetConstantBuffers(static_cast<uint8>(m_eReg), 1, m_pBuffer.GetAddressOf());
}

void ConstantBuffer::PushData(void* pData, uint32 iSize)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
	CONTEXT->Map(m_pBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);

	memcpy(mappedSubResource.pData, pData, iSize);
	CONTEXT->Unmap(m_pBuffer.Get(), 0);
}
