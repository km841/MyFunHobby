#pragma once
class PhysicsScene
{
public:
	PhysicsScene(PxScene* pScene);
	~PhysicsScene();

public:
	PxScene* GetScene() { return m_pScene; }

public:
	void AddActor(PxActor* pActor);
	void RemoveActor(PxActor* pActor);

private:
	PxScene* m_pScene;
};

