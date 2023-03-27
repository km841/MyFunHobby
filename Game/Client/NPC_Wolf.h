#pragma once
#include "GameObject.h"
class NPC_Wolf :
    public GameObject
{
public:
	NPC_Wolf();
	virtual ~NPC_Wolf();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();


private:


};

