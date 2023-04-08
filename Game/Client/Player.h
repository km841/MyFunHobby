#pragma once
#include "GameObject.h"

class PlayerState;
class StateMachine;
class Skul;
class GlobalEffect;
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
	FORCEINLINE PLAYER_STATE			 GetPlayerStateEnum()					       { return m_ePlayerState; }
	FORCEINLINE void					 SetPlayerStateEnum(PLAYER_STATE ePlayerState) { m_ePlayerState = ePlayerState; }
	FORCEINLINE shared_ptr<Skul>		 GetActiveSkul()							   { return m_pActiveSkul; }
	FORCEINLINE shared_ptr<GlobalEffect> GetDashSmokeEffect()						   { return m_pDashSmoke; }
	FORCEINLINE shared_ptr<GlobalEffect> GetJumpSmokeEffect()						   { return m_pJumpSmoke; }
	FORCEINLINE int32					 GetJumpCount()								   { return m_iJumpCount; }
	FORCEINLINE void					 DecreaseJumpCount()						   { m_iJumpCount -= 1; }
	FORCEINLINE void					 RefreshJumpCount()							   { m_iJumpCount = 2; }


	weak_ptr<PlayerState> GetPlayerState();
	void				  ChangePlayerState(PLAYER_STATE ePlayerState);
	shared_ptr<Skul>	  ObtainSkul(shared_ptr<Skul> pSkul);
	void				  SwapSkul();
	void				  RefreshAnimation(); 

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) override;
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) override;

private:
	void CreateDashSmokeAndAddedToScene();
	void CreateJumpSmokeAndAddedToScene();

private:
	std::array<shared_ptr<Skul>, MAX_SKULS> m_arrSkuls;
	shared_ptr<Skul>						m_pActiveSkul;
	shared_ptr<GlobalEffect>				m_pDashSmoke;
	shared_ptr<GlobalEffect>				m_pJumpSmoke;
	shared_ptr<StateMachine>				m_pStateMachine;
	PLAYER_STATE							m_ePlayerState;
	int32									m_iJumpCount;
};

