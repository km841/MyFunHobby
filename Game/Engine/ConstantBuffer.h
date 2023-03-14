#pragma once



class ConstantBuffer
{
	// 데이터를 운반하는 틀에 불과하다.
	// 렌더링될 때마다 이 틀에 각 오브젝트마다 다른 데이터를 담아서 넘겨주는 것
	// 예를 들면 위치정보의 경우 모든 오브젝트는 같은 틀의 위치정보를 가지지만 다른 값을 가지는 것

public:
	ConstantBuffer();
	~ConstantBuffer();

public:
	void Create(CBV_REGISTER eReg, uint32 iSize);

	// Transform이나 Material 구조체에 적당한 값을 세팅한다.
	// ConstantBuffer로 데이터를 GPU에 매핑한다.
	// 각 오브젝트마다 매핑 -> 쉐이더에서 해당 값으로 적절한 처리
	// 
	// Engine->GetConstantBuffer->PushData(data); -> 데이터 매핑
	// MeshRenderer의 Render에서 PushData를 호출해서 값 최종 전달

	void Mapping();
	void PushData(void* pData, uint32 iSize);



private:
	CBV_REGISTER		 m_eReg;
	ComPtr<ID3D11Buffer> m_pBuffer;



};

