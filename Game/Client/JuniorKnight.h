#pragma once
#include "Monster.h"
class JuniorKnight :
    public Monster
{
public:
	JuniorKnight();
	virtual ~JuniorKnight();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
	DECLARE_POOL(JuniorKnight);

};

