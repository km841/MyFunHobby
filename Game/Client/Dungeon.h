#pragma once

class Stage;
class DungeonEvent;
class Dungeon
{
public:
	friend class Stage;
	Dungeon(DUNGEON_TYPE eDungeonType, const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Dungeon();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();

	void AddEvent(shared_ptr<DungeonEvent> pDungeonEvent);
	void EventUpdate();

	void LoadEvent(const wstring& szEventScriptPath);

	DUNGEON_TYPE GetDungeonType() { return m_eDungeonType; }

protected:
	weak_ptr<Stage> m_pStage;
	DUNGEON_TYPE m_eDungeonType;
	const wstring m_szMapPath;

private:
	
	std::queue<shared_ptr<DungeonEvent>> m_qEventQueue;
};

