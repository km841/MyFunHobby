#pragma once

#include "PxEnvironment.h"
#include "PxDispatcher.h"

class Physics
{
public:
	Physics();
	~Physics();

public:
	void Init();
	void Update();
	
	shared_ptr<PxEnvironment>   GetEnvironment() { return m_pEnvironment; }
	shared_ptr<PxDispatcher>    GetDispatcher()  { return m_pDispatcher; }
	
private:
	PxScene*					GetScene();
	
private:
	shared_ptr<PxEnvironment>   m_pEnvironment;
	shared_ptr<PxDispatcher>    m_pDispatcher;
};

