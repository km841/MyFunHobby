#pragma once

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
	END,
};

enum class SCENE_TYPE
{
	TITLE,
	TOOL,
	TOWN,
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
	NONE,
};

enum class AXIS
{
	X,
	Y,
	Z,
};

enum
{
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
	PLAYER,
	MONSTER,
	NPC,
	TILE,
	AFTER_IMAGE,
	HUD = 29,
	UI = 30,
	END = 31,
};


enum
{
	LAYER_TYPE_COUNT = LAYER_TYPE::END,
};

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 1,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	SRV_REGISTER_COUNT = SRV_REGISTER::END,
};

enum class CAMERA_EFFECT : uint8
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

enum class UI_TYPE : uint8
{
	INVENTORY,
	DIALOGUE,
	MENU,
};

enum class PLAYER_STATE : uint8
{
	IDLE,
	WALK,
	JUMP_RISE,
	JUMP_FALL,
	JUMP_ATTACK,
	ATTACK_A,
	ATTACK_B,
	ATTACK_C,
	DASH,

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

	END
};


enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END),
};