#pragma once
#include "Scene.h"

class Scenes
{
	DECLARE_SINGLE(Scenes);

public:
    void Init();
    void Awake();
    void Start();
    void Update();
    void Render();

    shared_ptr<Scene> GetActiveScene() { return m_pCurScene; }
    void              ChangeScene(SCENE_TYPE eSceneType);

    Vec3 ScreenToWorldPosition(const Vec3& point, shared_ptr<class Camera> pCamera);

private:
    std::array<shared_ptr<Scene>, SCENE_TYPE_COUNT> m_arrScenes;
    shared_ptr<Scene>                          m_pCurScene;
};

