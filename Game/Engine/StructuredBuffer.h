#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer();
	~StructuredBuffer();

public:
	void Create(uint32 iElementSize, uint32 iElementCount, void* pInitialData = nullptr, bool bCpuAccess = false);
	void SetData(void* pData, uint32 iElementCount);
	void GetData(void* pData, uint32 iElementSize = 0);
	void PushGraphicsData(SRV_REGISTER eReg);
	void PushComputeUAVData(UAV_REGISTER eReg);
	void ClearGraphicsData();

	FORCEINLINE uint32 GetElementSize() { return m_iElementSize; }
	FORCEINLINE uint32 GetElementCount() { return m_iElementCount; }

private:
	void CreateBuffer(void* pInitialData);
	void CreateView();
	void CreateRWBuffer();

private:
	ComPtr<ID3D11Buffer> m_pWriteBuffer;
	ComPtr<ID3D11Buffer> m_pReadBuffer;
	ComPtr<ID3D11Buffer> m_pBuffer;

	ComPtr<ID3D11ShaderResourceView>  m_pSRV;
	ComPtr<ID3D11UnorderedAccessView> m_pUAV;

	uint32 m_iElementSize;
	uint32 m_iElementCount;

	uint32 m_iSRVSlot;
	uint32 m_iUAVSlot;

	void** m_ppNullptr;
};

