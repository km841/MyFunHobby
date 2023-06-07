#pragma once
#include "GameObject.h"

#define CHIMERA_SPRITES_COUNT 23
#define MAGNIFICATION 500

enum BlendMode : uint8
{
    BLEND_NORMAL,
    BLEND_ADDITIVE,
    BLEND_MULTIPLY,
    BLEND_SCREEN,
};

class ChimeraSprite;
class SpineResource;
class Chimera :
    public GameObject
{
public:
    Chimera();
    virtual ~Chimera();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Destroy();

public:
    void                       PlayAnimation(const string& szAnimName, bool bLoop = true);

private:
    void                       CreateChimeraSpritesAndAddedToScene();
    void                       CreateSpineData();
    void                       SpineDataUpdate();
    void                       ChimeraSpritesUpdate();
    std::vector<Vertex> CalculateVertexData(spine::Slot* pSlot, spine::RegionAttachment* pRegionAttachment);

private:
    spine::Skeleton*                     m_pSkeleton;
    spine::AnimationState*               m_pAnimationState;
                                    
    shared_ptr<SpineResource>            m_pSpineResource;
    std::vector<weak_ptr<ChimeraSprite>> m_vChimeraSprites;
};

