#pragma once
class Dungeon;

using DungeonInfo = std::tuple<bool, std::vector<DUNGEON_TYPE>, shared_ptr<Dungeon>>;
class Stage
	: public std::enable_shared_from_this<Stage>
{
public:
	Stage(STAGE_KIND eStageKind);
	virtual ~Stage();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void GoToNextDungeon(DUNGEON_TYPE eDungeonType);
	void AddDungeon(shared_ptr<Dungeon> pDungeon, const Vec4& vLimitRect = Vec4::Zero);
	void AlignDungeons();
	void Weaving(int32 iIndex, const std::vector<DungeonInfo>& vDungeonInfo, std::vector<bool>& vVisited);

protected:
	STAGE_KIND m_eStageKind;
	std::vector<shared_ptr<Dungeon>> m_vDungeons;
	weak_ptr<Dungeon> m_pActiveDungeon;
};

