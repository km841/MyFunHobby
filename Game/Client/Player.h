#pragma once
#include "GameObject.h"

class PlayerState;
class StateMachine;
class Skul;
class GlobalEffect;
class Item;
class Essence;
class Monster;

struct Clobber
{
	Clobber()
		: iDarkHeart(0)
		, iBoneFragments(0)
		, iGold(800)
		, iDarkQuartz(0)
	{}

	int32 iDarkHeart;
	int32 iBoneFragments;
	int32 iGold;
	int32 iDarkQuartz;
};

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
	FORCEINLINE void					 EnableSwapActiveFlag()						   { m_bSwapActiveFlag = true; }
	FORCEINLINE void					 DisableSwapActiveFlag()					   { m_bSwapActiveFlag = false; }
	FORCEINLINE bool					 IsSwapActiveFlag()							   { return m_bSwapActiveFlag; }
	FORCEINLINE bool					 IsSwapPossible()							   { return m_tSwapCooldown.IsFinished()/* && m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)]*/; }
	FORCEINLINE float					 GetSwapCooldownProgress()					   { return m_tSwapCooldown.GetProgress(); }
	FORCEINLINE weak_ptr<Skul>			 GetSkul(SKUL_INDEX eSkulIndex)				   { return m_arrSkuls[static_cast<uint8>(eSkulIndex)]; }
	FORCEINLINE Clobber*				 GetClobber()								   { return &m_Clobber; }
	// About states
	weak_ptr<PlayerState> GetPlayerState();
	void				  ChangePlayerState(PLAYER_STATE ePlayerState);

	// About skuls
	shared_ptr<Skul>	  ObtainSkul(shared_ptr<Skul> pSkul);
	void				  SwapSkul();
	void				  RefreshAnimation(); 
	void			      SkulCooldownUpdate();
	void			      SwapCooldownUpdate();

	// About items
	shared_ptr<Item>	   ObtainItem(shared_ptr<Item> pItem);
	void				   RemoveItem(shared_ptr<Item> pItem);
	ITEM_PLACE			   GetNearEmptyItemPlace();
	weak_ptr<Item>		   GetItem(ITEM_PLACE eItemPlace);
	std::vector<ITEM_KIND> GetItemList();
	void				   ItemUpdate();
	void				   TakeDamage(uint32 iDamage);
	void				   ActiveItemWhenHitTiming();
	void				   ActiveItemWhenDashTiming();
	void				   ActiveItemWhenJumpAttackEnterTiming();
	void				   ActiveItemWhenMonsterKillTiming();
	void				   ActiveItemWhenMonsterHitTiming(shared_ptr<Monster> pMonster);

	// About essence
	shared_ptr<Essence>   ObtainEssence(shared_ptr<Essence> pEssence);
	void				  EssenceUpdate();
	weak_ptr<Essence>	  GetEssence();
	void				  ActiveEssenceWhenDashEnterTiming();

	FORCEINLINE void Pause() { m_bPause = true; }
	FORCEINLINE void Play()  { m_bPause = false; }
	FORCEINLINE bool IsPause() { return m_bPause; }

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
	std::array<shared_ptr<Item>, MAX_ITEMS> m_arrItems;

	shared_ptr<Essence>					    m_pEssence;
	shared_ptr<Skul>						m_pActiveSkul;
	shared_ptr<GlobalEffect>				m_pDashSmoke;
	shared_ptr<GlobalEffect>				m_pJumpSmoke;
	shared_ptr<StateMachine>				m_pStateMachine;
	PLAYER_STATE							m_ePlayerState;
	int32									m_iJumpCount;

	Clobber									m_Clobber;
	Timer									m_tSwapCooldown;
	bool								    m_bSwapActiveFlag;
	bool									m_bPause;
};

