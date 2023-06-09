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

struct CameraShakeInfo
{
    CameraShakeInfo()
        : tCameraShakeTimer(0.f)
    {}

    CameraShakeInfo(float fEndTime, const Vec3& vImpulse)
        : tCameraShakeTimer(fEndTime)
        , vCameraShakeImpulse(vImpulse)
    {}

    Timer tCameraShakeTimer;
    Vec3 vCameraShakeImpulse;
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

    virtual void Destroy();

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
    void                                 RemoveSceneEvent();
    void                                 AddGameObject(shared_ptr<GameObject> pGameObject);
    std::vector<shared_ptr<GameObject>>& GetGameObjects(LAYER_TYPE eLayerType);
    void RemoveGameObject(shared_ptr<GameObject> pGameObject);
    void ShakeCameraAxis(float fMaxTime, const Vec3& vImpulse);

    bool IsExistTileThisPos(const Vec2& vTilePos);
    bool RaycastToTileGroup(shared_ptr<GameObject> pGameObject, const Vec3& vOrigin, const Vec3& vDir, float fMaxDistance);

    virtual void InitializeCameraAndPlayerPos() { }

    void RemoveLocalGroup(LAYER_TYPE eLocalLayerType);
    
    Vec4 GetObjectLimitRect();

    std::vector<DUNGEON_TYPE> GetDungeonGateTypesFromMapFile(const wstring& szPath);

private:
    void LoadBackground(std::wifstream& ifs);
    void LoadTile(std::wifstream& ifs);
    void LoadDungeonObject(std::wifstream& ifs);
    void LoadDecoObject(std::wifstream& ifs);
    void LoadLightObject(std::wifstream& ifs);

    void CreateDungeonGate(STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType, const wstring& szTexPath, const Vec3& vPos);
    void CreateDungeonWall(STAGE_KIND eStageKind, const wstring& szTexPath, const Vec3& vPos);
    void CreateTile(TILE_TYPE eTileType, const wstring& szTexPath, const Vec3& vPos);
    void CreateDecoObject(DECO_OBJECT_TYPE eDecoObjType, const wstring szTexPath, const Vec3& vPos);
    void CreateLightObject(const Vec3& vDiffuse, const Vec3& vAmbient, float fRange, const Vec3& vPos);

public:
    // Helper Functions
    weak_ptr<ComponentObject> GetMainCamera();
    weak_ptr<ComponentObject> GetUICamera();
    shared_ptr<Player>        GetPlayer();
    weak_ptr<ComponentObject> GetDirLight();
    weak_ptr<ComponentObject> GetBgm();

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

    std::queue<CameraShakeInfo> m_qCameraShakeInfo;
    CameraShakeInfo m_ActiveCameraShakeInfo;

    std::vector<shared_ptr<Light>> m_vLights;

    float m_fAccTime;
    bool m_bDebugMode;

protected:
    static std::array<std::vector<shared_ptr<GameObject>>, GLOBAL_OBJECT_TYPE_COUNT> s_vGlobalObjects;
    static std::vector<shared_ptr<Camera>>                                           s_vCameras;
    static std::vector<shared_ptr<Light>>                                            s_vLights;
    static shared_ptr<ComponentObject>                                               s_pBgm;
};