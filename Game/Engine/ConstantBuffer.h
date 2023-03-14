#pragma once



class ConstantBuffer
{
	// �����͸� ����ϴ� Ʋ�� �Ұ��ϴ�.
	// �������� ������ �� Ʋ�� �� ������Ʈ���� �ٸ� �����͸� ��Ƽ� �Ѱ��ִ� ��
	// ���� ��� ��ġ������ ��� ��� ������Ʈ�� ���� Ʋ�� ��ġ������ �������� �ٸ� ���� ������ ��

public:
	ConstantBuffer();
	~ConstantBuffer();

public:
	void Create(CBV_REGISTER eReg, uint32 iSize);

	// Transform�̳� Material ����ü�� ������ ���� �����Ѵ�.
	// ConstantBuffer�� �����͸� GPU�� �����Ѵ�.
	// �� ������Ʈ���� ���� -> ���̴����� �ش� ������ ������ ó��
	// 
	// Engine->GetConstantBuffer->PushData(data); -> ������ ����
	// MeshRenderer�� Render���� PushData�� ȣ���ؼ� �� ���� ����

	void Mapping();
	void PushData(void* pData, uint32 iSize);



private:
	CBV_REGISTER		 m_eReg;
	ComPtr<ID3D11Buffer> m_pBuffer;



};

