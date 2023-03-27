#pragma once
#include "GameObject.h"
class NPC_Wizard :
    public GameObject
{
public:
	NPC_Wizard();
	virtual ~NPC_Wizard();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
};

