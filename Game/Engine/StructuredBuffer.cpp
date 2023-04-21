#include "pch.h"
#include "StructuredBuffer.h"
#include "Engine.h"

StructuredBuffer::StructuredBuffer()
	: m_pWriteBuffer(nullptr)
	, m_pReadBuffer(nullptr)
	, m_iSRVSlot(0)
	, m_iUAVSlot(0)
	, m_ppNullptr(nullptr)
	, m_iElementSize(0)
	, m_iElementCount(0)
{
}

StructuredBuffer::~StructuredBuffer()
{
}

void StructuredBuffer::Create(uint32 iElementSize, uint32 iElementCount, void* pInitialData, bool bCpuAccess)
{
	m_iElementSize = iElementSize;
	m_iElementCount = iElementCount;

	CreateBuffer(pInitialData);
	CreateView();

	if (bCpuAccess)
		CreateRWBuffer();
}

void StructuredBuffer::SetData(void* pData, uint32 iElementCount)
{
	if (m_iElementCount < iElementCount)
	{
		Create(m_iElementSize, iElementCount, pData);
	}
	else
	{
		D3D11_MAPPED_SUBRESOURCE subResource = {};
		CONTEXT->Map(m_pWriteBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		memcpy(subResource.pData, pData, m_iElementSize * iElementCount);
		CONTEXT->Unmap(m_pWriteBuffer.Get(), 0);
	}

	CONTEXT->CopyResource(m_pBuffer.Get(), m_pWriteBuffer.Get());
}

void StructuredBuffer::GetData(void* pData, uint32 iElementSize)
{
	CONTEXT->CopyResource(m_pReadBuffer.Get(), m_pBuffer.Get());
}

void StructuredBuffer::PushGraphicsData(SRV_REGISTER eReg)
{
	uint8 iReg = static_cast<uint8>(eReg);
	CONTEXT->VSSetShaderResources(iReg, 1, m_pSRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(iReg, 1, m_pSRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(iReg, 1, m_pSRV.GetAddressOf());
	CONTEXT->CSSetShaderResources(iReg, 1, m_pSRV.GetAddressOf());
	m_iSRVSlot = iReg;
}

void StructuredBuffer::PushComputeUAVData(UAV_REGISTER eReg)
{
	m_iUAVSlot = static_cast<uint8>(eReg);
	CONTEXT->CSSetUnorderedAccessViews(m_iUAVSlot, 1, m_pUAV.GetAddressOf(), 0);
}

void StructuredBuffer::ClearGraphicsData()
{
	// Clear SRV
	CONTEXT->VSSetShaderResources(m_iSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));
	CONTEXT->DSSetShaderResources(m_iSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));
	CONTEXT->GSSetShaderResources(m_iSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));
	CONTEXT->HSSetShaderResources(m_iSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));
	CONTEXT->CSSetShaderResources(m_iSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));
	CONTEXT->PSSetShaderResources(m_iSRVSlot, 1, reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));

	// Clear UAV
	CONTEXT->CSSetUnorderedAccessViews(m_iUAVSlot, 1, reinterpret_cast<ID3D11UnorderedAccessView**>(&m_ppNullptr), 0);
}

void StructuredBuffer::CreateBuffer(void* pInitialData)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = m_iElementSize * m_iElementCount;
	desc.StructureByteStride = m_iElementSize;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
	desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	if (pInitialData)
	{
		D3D11_SUBRESOURCE_DATA subResource = {};
		subResource.pSysMem = pInitialData;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subResource, m_pBuffer.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
	else
	{
		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, m_pBuffer.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
}

void StructuredBuffer::CreateView()
{
	// Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = m_iElementCount;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;
		HRESULT hr = DEVICE->CreateShaderResourceView(m_pBuffer.Get(), &srvDesc, m_pSRV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	// Create UAV
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Buffer.NumElements = m_iElementCount;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

		HRESULT hr = DEVICE->CreateUnorderedAccessView(m_pBuffer.Get(), &uavDesc, m_pUAV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
}

void StructuredBuffer::CreateRWBuffer()
{
	// Create ReadBuffer
	{
		D3D11_BUFFER_DESC readDesc = { };
		readDesc.ByteWidth = m_iElementSize * m_iElementCount;
		readDesc.StructureByteStride = m_iElementSize;
		readDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		readDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		readDesc.Usage = D3D11_USAGE_DEFAULT;
		readDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		HRESULT hr = (DEVICE->CreateBuffer(&readDesc, nullptr, m_pReadBuffer.GetAddressOf()));
		assert(SUCCEEDED(hr));
	}

	// Create WriteBuffer
	{
		D3D11_BUFFER_DESC writeDesc = { };
		writeDesc.ByteWidth = m_iElementSize * m_iElementCount;
		writeDesc.StructureByteStride = m_iElementSize;
		writeDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		writeDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		writeDesc.Usage = D3D11_USAGE_DYNAMIC;
		writeDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = (DEVICE->CreateBuffer(&writeDesc, nullptr, m_pWriteBuffer.GetAddressOf()));
		assert(SUCCEEDED(hr));
	}
}
