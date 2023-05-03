#pragma once
class Dungeon;
class Stage
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

protected:
	STAGE_KIND m_eStageKind;
	std::vector<shared_ptr<Dungeon>> m_vDungeons;
	weak_ptr<Dungeon> m_pActiveDungeon;
};

