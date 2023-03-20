#include "pch.h"
#include "ContactCallback.h"

void ContactCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pPairs, PxU32 iNbPairs)
{
	for (PxU32 i = 0; i < iNbPairs; i++)
	{
		const PxContactPair& cp = pPairs[i];

		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			MessageBox(NULL, L"", L"", MB_OK);
		}
	}
}