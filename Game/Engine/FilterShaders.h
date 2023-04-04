#pragma once

class PlayerFilterShaders
	: public PxQueryFilterCallback
{
public:
	PlayerFilterShaders() { }
	~PlayerFilterShaders() { }

	virtual PxQueryHitType::Enum preFilter(
		const PxFilterData& filterData, const PxShape* pShape,
		const PxRigidActor* pActor, PxHitFlags& queryFlags);

	virtual PxQueryHitType::Enum postFilter(const PxFilterData& filterData, const PxQueryHit& queryHit);

private:

};

// =======================
// PlayerSimulationShaders
// =======================

static PxFilterFlags PlayerFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		if ((filterData1.word1 & filterData0.word0) || (filterData0.word1 & filterData1.word0))
		{
			pairFlags |= PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlag::eDEFAULT;
		}

		
	}
	// 트리거가 아닌 경우 충돌 플래그 생성
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	// 두 필터가 서로 충돌플래그가 세워져 있을 경우
	if ((filterData0.word0 & filterData1.word1) || (filterData1.word0 & filterData0.word1))
	{
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
		return PxFilterFlag::eDEFAULT;
	}

	return PxFilterFlag::eKILL;
}



