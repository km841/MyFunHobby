#include "pch.h"
#include "MonsterHitFrameProcessingTask.h"
#include "Animator.h"
#include "Animation.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Scenes.h"
#include "Scene.h"
#include "Sound.h"
#include "SoundSource.h"
#include "ComponentObject.h"
#include "Resources.h"

MonsterHitFrameProcessingTask::MonsterHitFrameProcessingTask(shared_ptr<GameObject> pGameObject, const Vec3& vOffset, const Vec3& vVolume, float fDamage, float fMaxDamage, const wstring& szHitSoundPath)
    : BehaviorTask(pGameObject)
    , m_fDamage(fDamage)
    , m_vVolume(vVolume)
    , m_vOffset(vOffset)
    , m_fMaxDamage(fMaxDamage)
    , m_szHitSoundPath(szHitSoundPath)
{
}

BEHAVIOR_RESULT MonsterHitFrameProcessingTask::Run()
{
    assert(m_pGameObject.lock()->GetAnimator());
    weak_ptr<Animation> pActiveAnimation = m_pGameObject.lock()->GetAnimator()->GetActiveAnimation();
    if (pActiveAnimation.lock()->IsHitFrame())
    {
        Vec3 vPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
        m_vOffset.x = fabs(m_vOffset.x);
        uint8 iDirection = static_cast<uint8>(m_pGameObject.lock()->GetDirection());
        vPos.x += iDirection ? -m_vOffset.x : m_vOffset.x;
        vPos.y += m_vOffset.y;

        if (m_fMaxDamage > m_fDamage)
        {
            float fDamage = static_cast<float>(RANDOM(static_cast<int32>(m_fDamage), static_cast<int32>(m_fMaxDamage)));
            GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vPos, m_vVolume, Vec3::Zero, fDamage);
        }
        else
        {
            GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vPos, m_vVolume, Vec3::Zero, m_fDamage);
        }

        if (!m_szHitSoundPath.empty())
        {
            SCENE_SOUND->SetClip(GET_SINGLE(Resources)->Load<Sound>(m_szHitSoundPath, m_szHitSoundPath));
            SCENE_SOUND->Play();
        }
        
        pActiveAnimation.lock()->CheckToHitFrame();
    }

    return BEHAVIOR_RESULT::SUCCESS;
}
