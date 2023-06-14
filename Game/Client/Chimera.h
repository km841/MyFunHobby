#pragma once
#include "Monster.h"

#define CHIMERA_SPRITES_COUNT 23
#define MAGNIFICATION 400

enum BlendMode : uint8
{
    BLEND_NORMAL,
    BLEND_ADDITIVE,
    BLEND_MULTIPLY,
    BLEND_SCREEN,
};

class ChimeraRoar;
class ChimeraSprite;
class SpineResource;
class MadScientist;
class Chimera :
    public Monster
{
public:
    Chimera(shared_ptr<MadScientist> pMadScientist);
    virtual ~Chimera();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Destroy();

    virtual void Enable();
    virtual void Disable();

public:
    static void  Listener(spine::AnimationState* state, 
        spine::EventType type, spine::TrackEntry* entry, spine::Event* event);

public:
    void                       PlayAnimation(const string& szAnimName, bool bLoop = true);
    void                       AddAnimation(const string& szAnimName, float fDelay, bool bLoop = true);
    void                       ClearAnimation() { m_szCurAnimationName = ""; m_pAnimationState->clearTrack(0); }
    void                       DestroyMadScientist();
    void                       DropParticles();
    void                       BreakFallingObject();
    void                       CreateRoarAndAddedToScene();
    void                       SetCurAnimationName(const string& szAnimName) { m_szCurAnimationName = szAnimName; }
    const string&              GetCurAnimationName() { return m_szCurAnimationName; }

private:
    void                       CreateChimeraSpritesAndAddedToScene();
    void                       CreateSpineData();
    void                       SpineDataUpdate();
    void                       ChimeraSpritesUpdate();

    
    std::vector<Vertex> CalculateVertexData(spine::Slot* pSlot, spine::RegionAttachment* pRegionAttachment);

private:
    static Chimera* s_pChimera;
    string m_szCurAnimationName;
    spine::Skeleton*                     m_pSkeleton;
    spine::AnimationState*               m_pAnimationState;
                                    
    shared_ptr<SpineResource>            m_pSpineResource;
    std::vector<weak_ptr<ChimeraSprite>> m_vChimeraSprites;

    weak_ptr<MadScientist> m_pMadScientist;
};

