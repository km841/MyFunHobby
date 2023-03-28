#include "pch.h"
#include "NPC_Ogre.h"

NPC_Ogre::NPC_Ogre()
	: GameObject(LAYER_TYPE::NPC)
{
}

NPC_Ogre::~NPC_Ogre()
{
}

void NPC_Ogre::Awake()
{
	GameObject::Awake();
}

void NPC_Ogre::Start()
{
	GameObject::Start();
}

void NPC_Ogre::Update()
{
	GameObject::Update();
}

void NPC_Ogre::LateUpdate()
{
	GameObject::LateUpdate();
}

void NPC_Ogre::FinalUpdate()
{
	GameObject::FinalUpdate();
}
