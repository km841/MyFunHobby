#pragma once
#include "Common.h"
#include "MapEditor.h"
#include "AnimationEditor.h"

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

	FORCEINLINE shared_ptr<MapEditor>     GetMapEditor() { return m_pMapEditor; }
	FORCEINLINE shared_ptr<AnimationEditor> GetAnimEditor() { return m_pAnimEditor; }

private:
	void    InitGui(HWND hHwnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	void    UpdateGui();
	
	

private:
	shared_ptr<MapEditor>       m_pMapEditor;
	shared_ptr<AnimationEditor> m_pAnimEditor;
	
};

