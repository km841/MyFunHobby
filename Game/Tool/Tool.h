#pragma once
#include "Common.h"
#include "TilePallete.h"

class Tool
{
public:
	Tool();
	~Tool();

public:
	void    Init(HWND hHwnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV);
	void    Update();
	void    Render();
	LRESULT DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	shared_ptr<TilePallete> GetPallete() { return m_pPallete; }

private:
	void    InitGui(HWND hHwnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	void    UpdateGui();
	

private:
	shared_ptr<TilePallete> m_pPallete;
};

