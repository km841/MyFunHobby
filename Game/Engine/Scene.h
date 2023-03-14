#pragma once

enum class SCENE_TYPE
{
    TITLE,
    TOOL,
    TOWN,
    END,
};

enum
{
    SCENE_TYPE_COUNT = SCENE_TYPE::END,
};


class GameObject;
class Camera;

class Scene
{
public:
	Scene();
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

    void AddGameObject(shared_ptr<GameObject> pGameObject);

    const std::vector<shared_ptr<GameObject>>& GetGameObjects() { return m_vGameObjects; }

protected:
    friend class Scenes;
    std::vector<shared_ptr<GameObject>>   m_vGameObjects;
    std::vector<shared_ptr<Camera>>       m_vCameras;
};

