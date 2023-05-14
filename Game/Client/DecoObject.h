#pragma once
#include "GameObject.h"
class DecoObject :
    public GameObject
{
public:
    DecoObject(DECO_OBJECT_TYPE eDecoObjType = DECO_OBJECT_TYPE::NORMAL);
    virtual ~DecoObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    FORCEINLINE DECO_OBJECT_TYPE GetDecoObjectType() { return m_eDecoObjType; }

protected:
    DECO_OBJECT_TYPE m_eDecoObjType;
};

