#pragma once
#include "MonoBehaviour.h"
class AlchemistFlaskThrowScript :
    public MonoBehaviour
{
public:
    AlchemistFlaskThrowScript();
    virtual ~AlchemistFlaskThrowScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateFlaskAndAddedToScene();

private:
    bool m_bThrowFlag;
};

