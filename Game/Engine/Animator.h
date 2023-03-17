#pragma once
#include "Component.h"

class Texture;
//struct AnimationData
//{
//    wstring           szName;
//    weak_ptr<Texture> pTexture;
//    Vec2              vLeftTop;
//    Vec2              vSpriteSize;
//
//
//};

class Animator :
    public Component
{
public:
    Animator();
    virtual ~Animator();

public:
    void CreateAnimation();

private:

};

