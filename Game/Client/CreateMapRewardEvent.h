#pragma once
#include "DungeonEvent.h"
class MapReward;
class CreateMapRewardEvent :
    public DungeonEvent
{
public:
	CreateMapRewardEvent(shared_ptr<ConditionBlock> pConditionBlock, GRADE eGrade, DUNGEON_TYPE eDungeonType);
	virtual ~CreateMapRewardEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	shared_ptr<MapReward> CreateItemReward(const Vec3& vPos);
	shared_ptr<MapReward> CreateGoldReward(const Vec3& vPos);
	shared_ptr<MapReward> CreateBoneReward(const Vec3& vPos);

	void CreateRewardEffectAddedToScene(const Vec3& vPos);

private:
	DUNGEON_TYPE m_eDungeonType;
	GRADE m_eGrade;
};

