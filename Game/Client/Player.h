#pragma once
#include "GameObject.h"

class PlayerState;
class StateMachine;
class Skul;

class Player :
	  public GameObject
{
public:
	friend class EventManager;

	Player();
	virtual ~Player();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	FORCEINLINE PLAYER_STATE	 GetPlayerStateEnum()					       { return m_ePlayerState; }
	FORCEINLINE void			 SetPlayerStateEnum(PLAYER_STATE ePlayerState) { m_ePlayerState = ePlayerState; }
	FORCEINLINE shared_ptr<Skul> GetActiveSkul()							   { return m_pActiveSkul; }

	void			 ChangePlayerState(PLAYER_STATE ePlayerState);
	shared_ptr<Skul> ObtainSkul(shared_ptr<Skul> pSkul);
	void			 SwapSkul();
	void			 RefreshAnimation(); 

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) override;

private:
	std::array<shared_ptr<Skul>, MAX_SKULS> m_arrSkuls;
	shared_ptr<Skul>						m_pActiveSkul;
	shared_ptr<StateMachine>				m_pStateMachine;
	PLAYER_STATE							m_ePlayerState;
};

