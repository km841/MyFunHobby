#pragma once
#include "Tool.h"

class Utility
{
public:
	Utility();
	~Utility();

public:
	void Init(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	void ToolUpdate();
	void ToolRender();

public:
	shared_ptr<Tool> GetTool() { return g_pTool; }
	wstring			 GetSelectedTileKey();

private:
	std::map<int32, wstring> m_mTileRrcMap;

};

