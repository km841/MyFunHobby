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


private:
	PLAYER_STATE m_ePlayerState;
	unique_ptr<StateMachine> m_pStateMachine;



};

