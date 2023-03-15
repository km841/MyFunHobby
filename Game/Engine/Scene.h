#pragma once




class GameObject;
class Camera;

class Scene
{
public:
	Scene(SCENE_TYPE eSceneType);
	virtual ~Scene();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Render();

public:
    virtual void Enter() { }
    virtual void Exit() { }

    SCENE_TYPE GetSceneType() { return m_eSceneType; }
    void AddGameObject(shared_ptr<GameObject> pGameObject);

    const std::vector<shared_ptr<GameObject>>& GetGameObjects() { return m_vGameObjects; }

protected:
    friend class Scenes;

    SCENE_TYPE m_eSceneType;

    std::vector<shared_ptr<GameObject>>   m_vGameObjects;
    std::vector<shared_ptr<Camera>>       m_vCameras;
};

