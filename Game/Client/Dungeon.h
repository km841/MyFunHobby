#pragma once

class Stage;
class DungeonEvent;
class Dungeon
{
public:
	friend class Stage;
	Dungeon(DUNGEON_TYPE eDungeonType, const wstring& szMapPath);
	virtual ~Dungeon();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void AddEvent(shared_ptr<DungeonEvent> pDungeonEvent);
	void EventUpdate();

	DUNGEON_TYPE GetDungeonType() { return m_eDungeonType; }

protected:
	weak_ptr<Stage> m_pStage;
	DUNGEON_TYPE m_eDungeonType;
	const wstring m_szMapPath;

private:
	
	std::queue<shared_ptr<DungeonEvent>> m_qEventQueue;
};

