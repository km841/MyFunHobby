#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

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
#include <array>
#include <spine/spine.h>

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

struct LightData
{
	ImVec3 vDiffuse;
	ImVec3 vAmbient;
	float fRadius;
	ImVec3 vLightPos;
};

struct BackgroundData
{
	wstring szBGImagePath;
	ImVec3 vBGPos;
	ImVec3 vBGScale;
	ImVec3 vBGSpeed;
};

enum class SRV_KIND
{
	TILE,
	DUNGEON_GATE,
	DUNGEON_WALL,
	DECO_OBJECT,
	END,
};

enum
{
	SRV_KIND_COUNT = SRV_KIND::END,
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

enum class TILE_TYPE
{
	WALL,
	NONE,
	FOOTHOLD,
};


struct TileData
{
	TileData() = default;
	TileData(TILE_TYPE eTileType, const wstring& szTexPath, ImVec2 vTilePos)
		: szTexPath(szTexPath), vTilePos(vTilePos), eTileType(eTileType)
	{}

	TILE_TYPE eTileType;
	wstring szTexPath;
	ImVec2 vTilePos;
};

enum class STAGE_KIND : uint8
{
	BLACK_LAB,
	CITADEL_OF_FATE,
	END,
};

enum class DUNGEON_TYPE : uint8
{
	BASE_CAMP,
	DUNGEON_ITEM,
	DUNGEON_GOLD,
	DUNGEON_BONE,
	SHOP,
	VICE_BOSS,
	STAGE_BOSS,
	END,
};

enum
{
	STAGE_KIND_COUNT = STAGE_KIND::END,
};

enum class DUNGEON_OBJ_TYPE
{
	DUNGEON_GATE,
	DUNGEON_WALL,
};

enum class DECO_OBJECT_TYPE
{
	LIGHT,
	NORMAL,
};

struct DungeonObjData
{
	DUNGEON_OBJ_TYPE eDungeonObjType;

	STAGE_KIND eStageKind;
	DUNGEON_TYPE eDungeonType;
	wstring szTexPath;
	ImVec2 vDOPos;
};

struct DecoObjData
{
	DECO_OBJECT_TYPE eDecoObjType;

	wstring szTexPath;
	ImVec2 vDecoPos;
};

struct TileMapData
{
	wstring szName;
	uint32  iTileCount;
	std::vector<TileData> vTileData;
	std::vector<DungeonObjData> vDOData;
	std::vector<DecoObjData> vDecoData;
	std::vector<LightData> vLightData;
};

enum class CONDITION_TYPE : uint8
{
	ALWAYS_TRUE,
	ALL_MONSTER_DEAD_IN_DUNGEON,
	PLAYER_POS_X_EXCEEDS_800,
	PLAYER_POS_X_EXCEEDS_1000,
	TAKE_MAP_REWARD,
	END,
};

enum class DUNGEON_EVENT_KIND : uint8
{
	MONSTER_SPAWN,
	CREATE_MAP_REWARD,
	PLAYER_TELEPORT,
	DUNGEON_GATE_OPEN,
	PLAYER_WALK,
	PLAYER_STATE_CHANGE,
	MONSTER_STATE_CHANGE,
	OBJECT_ENABLE,
	OBJECT_DISABLE,
	ACTIVE_DIALOGUE,
	PLAYER_HUD_DISABLE,
	PLAYER_HUD_ENABLE,
	NOTHING,
	CHANGE_ANIMATION,
	CHANGE_OBJECT_POS,
	AWAKEN_CHIMERA,
	CAMERA_FIXED,
	CAMERA_UNFIX,
	PAUSE,
	PLAY,
	ENABLE_BOSS_HP_HUD,
	END,
};

enum class MONSTER_KIND : uint16
{
	JUNIOR_KNIGHT,
	ERODED_KNIGHT,
	ERODED_HEAVY_INFANTRY,
	ERODED_ENT,
	ALCHEMIST,
	NONE,
	END,
};

enum class GRADE
{
	NORMAL,
	RARE,
	UNIQUE,
	LEGENDARY,
	END,
};

enum
{
	CONDITION_TYPE_COUNT = CONDITION_TYPE::END,
	DUNGEON_EVENT_COUNT = DUNGEON_EVENT_KIND::END,
	MONSTER_KIND_COUNT = MONSTER_KIND::END,
	GRADE_TOTAL_COUNT = GRADE::END,
};



struct EventInfo
{
	EventInfo() { memset(this, 0, sizeof(EventInfo)); }
	CONDITION_TYPE eCondition;
	DUNGEON_EVENT_KIND eEventKind;
	int32 eEnum1;
	int32 eEnum2;
	ImVec3 vVec3;
};

extern shared_ptr<class Tool> g_pTool;

wstring s2ws(const string& s);
string ws2s(const wstring& ws);

wstring AbsolutePathToRelativePath(const wstring& szAbsolutePath);
