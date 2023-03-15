#pragma once
#include "GameObject.h"

class Tile :
    public GameObject
{
public:
    Tile();
    virtual ~Tile();

    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

private:
    DECLARE_POOL(Tile);
};

