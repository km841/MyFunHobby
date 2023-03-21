#pragma once
#include "PxEnvironmentSetting.h"
#include "PhysicsScene.h"

class PxEnvironment
{
public:
	PxEnvironment();
	~PxEnvironment();

public:
	void Init();

public:
	PxFoundation*					 GetFoundation()		{ return m_pSetting->GetFoundation(); }
	PxPhysics*						 GetPhysics()			{ return m_pSetting->GetPhysics(); }
	PxControllerManager*			 GetControllerManager() { return m_pControllerMgr; }

	shared_ptr<PhysicsScene>		 GetPhysScene()			{ return m_pPhysScene; }
			 
	void							 CreatePhysicsScene(const PxSceneDesc& sceneDesc);
	void                             ConnectDebuggerToScene();


private:							 
	void CreateScene(const PxSceneDesc& sceneDesc);
	void CreateControllerManager();
	void CreateDebugger(const char* szHost, int32 iPort);
	void ConnectDebugger();
	

private:
	shared_ptr<PhysicsScene>		 m_pPhysScene;
	shared_ptr<PxEnvironmentSetting> m_pSetting;

	PxPvdTransport*					 m_pTransfort;
	PxPvd*							 m_pPvd;
	PxPvdSceneClient*				 m_pSceneClient;
	PxScene*						 m_pScene;
	PxControllerManager*			 m_pControllerMgr;
};
