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

    FORCEINLINE SCENE_TYPE               GetSceneType() { return m_eSceneType; }
    void                                 AddGameObject(shared_ptr<GameObject> pGameObject);
    void                                 AddObjectAtSortedIndex(shared_ptr<GameObject> pGameObject);

    std::vector<shared_ptr<GameObject>>& GetGameObjects(LAYER_TYPE eLayerType);

public:
    virtual void Load(const wstring& szPath);

protected:
    friend class Scenes;

    SCENE_TYPE m_eSceneType;
    std::array<std::vector<shared_ptr<GameObject>>, LAYER_TYPE_COUNT> m_vGameObjects;
    std::vector<shared_ptr<Camera>>                                   m_vCameras;
};