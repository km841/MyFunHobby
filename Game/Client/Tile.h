#pragma once
#include "GameObject.h"

class Tile :
    public GameObject
{
public:
    Tile();
    virtual ~Tile();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

public:
    virtual void Save(const wstring& szPath) override;
    virtual void Load(const wstring& szPath) override;

private:
    DECLARE_POOL(Tile);
};

