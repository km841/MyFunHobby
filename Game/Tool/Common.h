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
#include "ImGuiFileDialog.h"

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

using std::wstring;
using std::string;

#include <filesystem>
namespace fs = std::filesystem;
using namespace Microsoft::WRL;

struct ImVec3
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

struct BackgroundData
{
	wstring szBGImagePath;
	ImVec3 vBGPos;
	ImVec3 vBGScale;
};


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

struct FrameData
{
	wstring szName;
	wstring szTexPath;
	ImVec2 vLTPos;
	ImVec2 vSize;
	ImVec2 vOffset;
	float  fDuration;
	int32  iFrameCount;
};

struct TileData
{
	TileData() = default;
	TileData(const wstring& szTexPath, ImVec2 vTilePos)
		: szTexPath(szTexPath), vTilePos(vTilePos)
	{}
	wstring szTexPath;
	ImVec2 vTilePos;
};

struct TileMapData
{
	wstring szName;
	uint32  iTileCount;
	std::vector<TileData> vTileData;
};

extern shared_ptr<class Tool> g_pTool;

wstring s2ws(const string& s);
string ws2s(const wstring& ws);

wstring AbsolutePathToRelativePath(const wstring& szAbsolutePath);
