#pragma once
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);
public:
	void SetCollisionGroup(LAYER_TYPE iFirst, LAYER_TYPE iSecond);
	void Update();

private:
	void SetCollisionFlag(int32 iFirst, int32 iSecond);

private:
	std::array<std::bitset<LAYER_TYPE_COUNT>, LAYER_TYPE_COUNT> m_arrColGroup;
};

