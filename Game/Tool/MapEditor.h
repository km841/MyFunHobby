#pragma once
#include "GuiBase.h"
class MapEditor :
    public GuiBase
{
public:
    // 던전 이벤트 추가
    // 맵 구조물 추가
    // 배경 추가
    MapEditor();
    ~MapEditor();

    void Init();
    void Update();

public:


};

