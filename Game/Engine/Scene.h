#pragma once

class GameObject;
class Camera;
class AfterImage;
class Light;
class ComponentObject;
class Player;

struct SceneEventInfo
{
    EVENT_TYPE eEventType;
    uint8 iDetailEnum;
    float fEndTime;
    float fCurTime;
};

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
    virtual void Exit()  { }
    void Render_Lights();
    void Render_Final();
    void Render_Forward();
    void Render_Deferred();
    void Render_Font();
    void PushLightData();
    void EventUpdate();
    void CameraShakeUpdate();

    FORCEINLINE void                     RegisterSceneEvent(EVENT_TYPE eEventType, uint8 iDetailEnum, float fEndTime) { m_vSceneEvents.push_back(SceneEventInfo{ eEventType, iDetailEnum, fEndTime }); }
    FORCEINLINE SCENE_TYPE               GetSceneType() { return m_eSceneType; }
    void                                 AddGameObject(shared_ptr<GameObject> pGameObject);
    std::vector<shared_ptr<GameObject>>& GetGameObjects(LAYER_TYPE eLayerType);
    void RemoveGameObject(shared_ptr<GameObject> pGameObject);
    void ShakeCameraAxis(float fMaxTime, const Vec3& vImpulse);

    virtual void InitializeCameraAndPlayerPos() { }

    void RemoveLocalGroup(LAYER_TYPE eLocalLayerType);

private:
    void LoadBackground(std::wifstream& ifs);
    void LoadTile(std::wifstream& ifs);
    void LoadDungeonObject(std::wifstream& ifs);

    void CreateDungeonGate(STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType, const wstring& szTexPath, const Vec3& vPos);
    void CreateDungeonWall(STAGE_KIND eStageKind, const wstring& szTexPath, const Vec3& vPos);
    void CreateTile(TILE_TYPE eTileType, const wstring& szTexPath, const Vec3& vPos);

public:
    // Helper Functions
    weak_ptr<ComponentObject> GetMainCamera();
    weak_ptr<ComponentObject> GetUICamera();
    shared_ptr<Player>          GetPlayer();

public:
    virtual void Load(const wstring& szPath);

protected:
    void AwakeLocalObjects();
    void AwakeGlobalObjects();

protected:
    friend class Scenes;
    SCENE_TYPE m_eSceneType;

    std::array<std::vector<shared_ptr<GameObject>>, SCENE_OBJECT_TYPE_COUNT> m_vSceneObjects;

    std::vector<SceneEventInfo>                                              m_vSceneEvents;

    float m_fFadeEffectRatio;
    EVENT_TYPE m_eActiveSceneEvent;

    Timer m_tCameraShakeTimer;
    Vec3 m_vCameraShakeImpulse;

    std::vector<shared_ptr<Light>> m_vLights;
    

protected:
    static std::array<std::vector<shared_ptr<GameObject>>, GLOBAL_OBJECT_TYPE_COUNT> s_vGlobalObjects;
    static std::vector<shared_ptr<Camera>>                                           s_vCameras;
    static std::vector<shared_ptr<Light>>                                            s_vLights;
};