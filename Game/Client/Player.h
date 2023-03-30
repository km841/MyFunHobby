#pragma once
#include "GameObject.h"

class PlayerState;
class PlayerInterfaceHUD;
class StateMachine;

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
	FORCEINLINE PLAYER_STATE GetPlayerStateEnum()					       { return m_ePlayerState; }
	FORCEINLINE void		 SetPlayerStateEnum(PLAYER_STATE ePlayerState) { m_ePlayerState = ePlayerState; }

	void ChangePlayerState(PLAYER_STATE ePlayerState);

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) override;

private:
	shared_ptr<StateMachine>	   m_pStateMachine;
	PLAYER_STATE				   m_ePlayerState;
	
};

