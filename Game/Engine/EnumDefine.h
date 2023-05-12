#pragma once

enum class EVENT_TYPE
{
	SCENE_CHANGE,
	OBJECT_ADDED_TO_SCENE,
	OBJECT_REMOVE_TO_SCENE,
	OBJECT_RETURN_TO_POOL,
	FORCE_ON_OBJECT_EVENT,
	PLAYER_CHANGE_STATE,
	SCENE_FADE_EVENT,
	PAUSE_EVENT,
	PLAY_EVENT,
	GO_TO_NEXT_DUNGEON,
	END,
};


enum class CBV_REGISTER : uint8
{
	b0,
	b1,
	b2,
	b3,
	b4,


	END,
};

enum class SRV_REGISTER : uint8
{
	t0,
	t1,
	t2,
	t3,
	t4,
	t5,
	t6,
	t7,
	t8,
	t9,


	END,
};

enum class UAV_REGISTER : uint8
{
	u0,
	u1,
	u2,
	u3,
	u4,

	END,
};

enum class CONSTANT_BUFFER_TYPE
{
	TRANSFORM,
	MATERIAL,
	LIGHT,
	END,
};

enum class SCENE_TYPE
{
	TITLE,
	TOOL,
	TOWN,
	SHOP,
	DUNGEON,
	END,
};

enum class DIRECTION
{
	RIGHT,
	LEFT,
};

enum class COLLISION_SIDE
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	END,
};

enum class AXIS
{
	X,
	Y,
	Z,
};

enum
{
	COLLISION_SIDE_COUNT = COLLISION_SIDE::END,
	SCENE_TYPE_COUNT = SCENE_TYPE::END,
};

enum
{
	CONSTANT_BUFFER_TYPE_COUNT = CONSTANT_BUFFER_TYPE::END,
	INITIAL_POOL_COUNT = 1000,
};

enum class LAYER_TYPE : uint8
{
	UNKNOWN = 0,
	BACKGROUND,
	MONSTER,
	NPC,
	TILE,
	DECO,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	PARTICLE,
	MONSTER_HUD,
	EVENT_OBJECT,
	DUNGEON_GATE,
	DUNGEON_WALL,
	DROP_ITEM,
	DROP_ESSENCE,
	MAP_REWARD,
	LOCAL_EFFECT,
	SCENE_OBJECT_END = 22,
	POSSESSION = 23,
	COMPONENT_OBJECT = 24,
	GLOBAL_EFFECT = 25,
	AFTER_IMAGE = 26,
	PLAYER = 27,
	HUD = 28,
	INTERFACE_EFFECT = 29,
	UI = 30,
	END = 31,
};

enum class SHADER_TYPE : uint8
{
	FORWARD,
	DEFERRED,
	LIGHTING,
	PARTICLE,
	COMPUTE,
	VELOCITY,
};

enum
{
	LAYER_TYPE_COUNT = LAYER_TYPE::END,
	GLOBAL_OBJECT_TYPE_COUNT = LAYER_TYPE_COUNT - static_cast<uint8>(LAYER_TYPE::SCENE_OBJECT_END) - 1,
	SCENE_OBJECT_TYPE_COUNT = LAYER_TYPE_COUNT - GLOBAL_OBJECT_TYPE_COUNT,
};

enum
{
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	SRV_REGISTER_COUNT = SRV_REGISTER::END,
};

enum class SCENE_FADE_EFFECT : uint8
{
	NONE,
	FADE_IN,
	FADE_OUT,
};

enum class FADE_TYPE : uint8
{
	FADE_IN,
	FADE_OUT,
};

enum class OBJECT_LEVEL_TYPE : uint8
{
	OBJECT_LEVEL_1,
	OBJECT_LEVEL_2,
	OBJECT_LEVEL_3,
	OBJECT_LEVEL_4,
	OBJECT_LEVEL_5,
};

enum class INTERFACE_TYPE : uint8
{
	INVENTORY,
	DIALOGUE,
	MENU,
	//---------------
	PLAYER_INTERFACE,
	PLAYER_HEALTH_BAR,
	PLAYER_SKILL_BOX_FIRST,
	PLAYER_SKUL_THUMNAIL,
	PLAYER_HIT,
	MOUSE_POINTER,
	BASECAMP_OPENING,
	END,
};

enum class UI_TYPE : uint8
{
	INVENTORY,
	DIALOGUE,
	MENU,
	END,
};

enum class HUD_TYPE : uint8
{
	PLAYER_INTERFACE,
	PLAYER_HEALTH_BAR,
	PLAYER_SKILL_BOX_FIRST,
	PLAYER_SKUL_THUMNAIL,
	PLAYER_HIT,
	MOUSE_POINTER,
	BASECAMP_OPENING,
	END,
};

enum class SKILL_TYPE : uint8
{
	NONE,
	INSTANT,
	CHARGING,
};

enum class ESSENCE_TYPE : uint8
{
	INSTANT,
	CONTINUOUS,
	END,
};

enum class ESSENCE_KIND : uint8
{
	LYWEASEL,
	WISP,
	END,
};

enum class ENGRAVE : uint8
{
	SUN_AND_MOON, // 해와달
	SOUL, // 정령
	WISDOM, // 지혜
	RAPIDITY, // 신속
	MAGIC_TOOL, // 마도구
	SOAR, // 비상
	MISFORTUNE, // 불운
	ARMS, // 무구
	KNELL, // 흉조
	END,
};

enum
{
	UI_MAX_COUNT = UI_TYPE::END,
	HUD_MAX_COUNT = HUD_TYPE::END
};

enum class PLAYER_STATE : uint8
{
	IDLE,
	WALK,
	JUMP_RISE,
	JUMP_FALL,
	JUMP_ATTACK,
	DASH,
	SKILL,
	PATH,
	SWAP,
	CHARGING,
	ATTACK,
	ATTACK_A,
	ATTACK_B,
	ATTACK_C,
	ATTACK_D,
	ATTACK_E,
	END,
};

enum class OBJECT_TYPE : uint8
{
	NONE,
	ANIMATION,
	GAMEOBJECT,
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,
	PROPERTIES,
	ITEM,
	ESSENCE,

	END
};

enum
{
	PLAYER_STATE_COUNT = static_cast<uint8>(PLAYER_STATE::END),
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END),
};

enum class ENGRAVE_STATE
{
	DEACTIVATE,
	ACTIVATE,
	FULL_ACTIVATE,
	END,
};

enum class ITEM_PLACE
{
	PLACE_1_1,
	PLACE_1_2,
	PLACE_1_3,
	PLACE_2_1,
	PLACE_2_2,
	PLACE_2_3,
	PLACE_3_1,
	PLACE_3_2,
	PLACE_3_3,
	END,
};

enum class ITEM_KIND
{
	FORBIDDEN_SWORD,
	EVIL_SWORD_KIRION,

};

enum class SKUL_KIND
{
	LITTLE_BONE,
	HIGH_WARLOCK,
};

enum class SKUL_TYPE
{
	SPEED,
	BALANCE,
	POWER,
};



enum class SKUL_INDEX
{
	FIRST,
	SECOND,
	END,
};

enum class SKILL_INDEX
{
	FIRST,
	SECOND,
	END,
};

enum
{
	MAX_ENUMS = 8,
	MAX_SKULS = SKUL_INDEX::END,
	MAX_SKILLS = SKILL_INDEX::END,
	MAX_ITEMS = ITEM_PLACE::END,
	END_POINT = -1,
};

enum class LITTLE_BONE_STATE
{
	HAS_HEAD,
	NO_HEAD,
};

enum class AFTERIMAGE_TYPE
{
	DASH,
	SWAP,
};

enum class PARTICLE_DIRECTION
{
	TOP,
	RIGHT_TOP,
	RIGHT,
	RIGHT_BTM,
	BTM,
	LEFT_BTM,
	LEFT,
	LEFT_TOP,
	END,
};

enum
{
	PARTICLE_DIRECTION_COUNT = PARTICLE_DIRECTION::END,
};



