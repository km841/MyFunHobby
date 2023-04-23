#include "pch.h"
#include "ContactCallback.h"
#include "GameObject.h"
#include "Collider.h"
#include "Engine.h"


void ContactCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pPairs, PxU32 iNbPairs)
{
    for (PxU32 i = 0; i < iNbPairs; i++)
    {
        const PxContactPair& cp = pPairs[i];

        if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            if (pairHeader.actors[0]->userData && pairHeader.actors[1]->userData)
            {
                GameObject* pContact = static_cast<GameObject*>(pairHeader.actors[0]->userData);
                GameObject* pOther = static_cast<GameObject*>(pairHeader.actors[1]->userData);

                if (pContact->GetCollider())
                    pContact->GetCollider()->OnCollisionEnter(pOther->GetCollider());
            }
        }
        else if (cp.events & PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            if (pairHeader.actors[0]->userData && pairHeader.actors[1]->userData)
            {
                GameObject* pContact = static_cast<GameObject*>(pairHeader.actors[0]->userData);
                GameObject* pOther = static_cast<GameObject*>(pairHeader.actors[1]->userData);

                //if (pContact->GetCollider())
                //    pContact->GetCollider()->OnCollisionExit(pOther->GetCollider());
            }
        }
    }
}

void ContactCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        const PxTriggerPair& pair = pairs[i];

        if (pair.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            if (pair.triggerActor && pair.otherActor)
            {
                GameObject* pTrigger = static_cast<GameObject*>(pair.triggerActor->userData);
                GameObject* pOther = static_cast<GameObject*>(pair.otherActor->userData);

                if (pTrigger->GetCollider())
                    pTrigger->GetCollider()->OnTriggerEnter(pOther->GetCollider());

                if (pOther->GetCollider())
                    pOther->GetCollider()->OnTriggerEnter(pTrigger->GetCollider());
            }
        }

        if (pair.status & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
        {
            if (pair.triggerActor && pair.otherActor)
            {
                GameObject* pTrigger = static_cast<GameObject*>(pair.triggerActor->userData);
                GameObject* pOther = static_cast<GameObject*>(pair.otherActor->userData);

                if (pTrigger->GetCollider())
                    pTrigger->GetCollider()->OnTriggerStay(pOther->GetCollider());
            }
        }

        if (pair.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            if (pair.triggerActor && pair.otherActor)
            {
                GameObject* pTrigger = static_cast<GameObject*>(pair.triggerActor->userData);
                GameObject* pOther = static_cast<GameObject*>(pair.otherActor->userData);

                //if (pTrigger->GetCollider())
                //    pTrigger->GetCollider()->OnTriggerExit(pOther->GetCollider());
            }
        }
    }
}
