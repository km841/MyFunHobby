#pragma once
#include "GameObject.h"

class NPC_Witch :
    public GameObject
{
public:
	NPC_Witch();
	virtual ~NPC_Witch();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();


private:


};

