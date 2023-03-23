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

public:
    virtual void Save(const wstring& szPath) override;
    virtual void Load(const wstring& szPath) override;

public:
    void SetTileTexPath(const wstring& szTexPath) { m_szTexPath = szTexPath; }
    const wstring& GetTileTexPath() { return m_szTexPath; }

private:
    DECLARE_POOL(Tile);

    wstring m_szTexPath;

};

