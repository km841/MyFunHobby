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

	void LoadEventFromFile(const wstring& szEventScriptPath);
	void CalculateCameraLimitArea();
	FORCEINLINE void SetLimitRect(const Vec4& vLimitRect) { m_vLimitRect = vLimitRect; }
	FORCEINLINE bool IsVisited() { return m_bVisited; }
	void SetCameraLimitArea();

	DUNGEON_TYPE GetDungeonType() { return m_eDungeonType; }

protected:
	weak_ptr<Stage> m_pStage;
	DUNGEON_TYPE m_eDungeonType;
	const wstring m_szMapPath;
	Vec4 m_vLimitRect;
	bool m_bVisited;

private:
	std::queue<shared_ptr<DungeonEvent>> m_qEventQueue;
};

