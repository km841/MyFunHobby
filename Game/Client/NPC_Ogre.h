#pragma once
#include "GameObject.h"
class NPC_Ogre :
    public GameObject
{
public:
	NPC_Ogre();
	virtual ~NPC_Ogre();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();


private:

};

