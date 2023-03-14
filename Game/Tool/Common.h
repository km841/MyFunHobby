#pragma once
#include <Windows.h>
#include <memory>

#include "d3d11.h"
#include <d3dcompiler.h>
#include <dxgi.h>

#include <wrl.h>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <vector>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using std::shared_ptr;
using std::make_shared;

using std::unique_ptr;
using std::make_unique;

#include <filesystem>
namespace fs = std::filesystem;


using namespace Microsoft::WRL;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define DECLARE_SINGLE(type)  \
private:					  \
	type() {}				  \
	~type() {}				  \
							  \
public:						  \
	static type* GetInstance()\
	{						  \
		static type instance; \
		return &instance;	  \
	}						  \

#define GET_SINGLE(type) type::GetInstance()

extern shared_ptr<class Tool> g_pTool;