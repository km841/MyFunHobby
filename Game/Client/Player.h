#pragma once
#include "GameObject.h"

class PlayerState;
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
	PLAYER_STATE GetPlayerStateEnum()					   { return m_ePlayerState; }
	void		 SetPlayerState(PLAYER_STATE ePlayerState) { m_ePlayerState = ePlayerState; }

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) override;


private:
	PLAYER_STATE m_ePlayerState;
	unique_ptr<StateMachine> m_pStateMachine;
	int32		 m_iTileCollisionCount;



};

