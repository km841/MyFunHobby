#pragma once
#include "Tool.h"

class Utility
{
public:
	Utility();
	~Utility();

public:
	void			 Init(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	void			 ToolUpdate();
	void			 ToolRender();

public:
	FORCEINLINE shared_ptr<Tool> GetTool()    const { return g_pTool; }
	FORCEINLINE wstring			 GetTexPath() const { return m_szTexPath; }
	wstring						 GetSelectedTileKey();

private:
	std::map<int32, wstring> m_mTileRrcMap;
	wstring					 m_szTexPath;

};

