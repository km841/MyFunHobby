#pragma once
class Context
{
public:
	Context();
	~Context();

public:
	void Init(ComPtr<ID3D11DeviceContext> pContext);

	FORCEINLINE ComPtr<ID3D11DeviceContext> GetContext() { return m_pContext; }

private:
	ComPtr<ID3D11DeviceContext> m_pContext;

};

