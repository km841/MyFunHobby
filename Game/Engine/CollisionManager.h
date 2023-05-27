#pragma once
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);
public:
	void SetCollisionGroup(LAYER_TYPE iFirst, LAYER_TYPE iSecond);
	void Update();

	void SetForceInLayer(LAYER_TYPE eLayerType, const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse);
	void SetForceInPlayerAndTakeDamage(const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse, float fDamage);
	void SetForceInLayerAndFollowPlayer(LAYER_TYPE eLayerType, const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse);
private:
	void SetCollisionFlag(int32 iFirst, int32 iSecond);
	

private:
	std::array<std::bitset<LAYER_TYPE_COUNT>, LAYER_TYPE_COUNT> m_arrColGroup;
};

