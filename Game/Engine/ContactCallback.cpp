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
				GameObject* pFirst =  static_cast<GameObject*>(pairHeader.actors[0]->userData);
				GameObject* pSecond = static_cast<GameObject*>(pairHeader.actors[1]->userData);

				if (pFirst->GetCollider())
					pFirst->GetCollider()->OnCollision(pSecond->GetCollider());
			}
		}
	}
}