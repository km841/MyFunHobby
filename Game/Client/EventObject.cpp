#include "pch.h"
#include "EventObject.h"

EventObject::EventObject()
	: GameObject(LAYER_TYPE::EVENT_OBJECT)
{
}

EventObject::~EventObject()
{
}

void EventObject::Awake()
{
	GameObject::Awake();
}

void EventObject::Start()
{
	GameObject::Start();
}

void EventObject::Update()
{
	GameObject::Update();
}

void EventObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void EventObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void EventObject::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	int a = 0;
}

void EventObject::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
