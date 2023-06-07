#pragma once
#include "Scene.h"

class Camera;
class Scenes
{
	DECLARE_SINGLE(Scenes);

public:
    void Init();
    void Awake();
    void Start();
    void Update();
    void Render();
    void Destroy();

    FORCEINLINE shared_ptr<Scene> GetActiveScene() const { return m_pActiveScene; }
    void ChangeScene(SCENE_TYPE eSceneType);

    Vec3 ScreenToWorldPosition(const Vec3& vPoint, shared_ptr<Camera> pCamera);
    Vec3 WorldToScreenPosition(const Vec3& vPoint, shared_ptr<Camera> pCamera);

private:
    friend class EventManager;
    std::array<shared_ptr<Scene>, SCENE_TYPE_COUNT> m_arrScenes;
    shared_ptr<Scene>                               m_pActiveScene;
};

