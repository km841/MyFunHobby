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

enum
{
	SCENE_TYPE_COUNT = SCENE_TYPE::END,
};

enum
{
	CONSTANT_BUFFER_TYPE_COUNT = CONSTANT_BUFFER_TYPE::END,
	INITIAL_POOL_COUNT = 1000,
};

enum class LAYER_TYPE : uint32
{
	UNKNOWN = 0,
	PLAYER,
	MONSTER,
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