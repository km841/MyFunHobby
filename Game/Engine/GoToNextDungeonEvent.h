#pragma once
#include "Event.h"
class Stage;
class GoToNextDungeonEvent :
    public Event
{
public:
    explicit GoToNextDungeonEvent(shared_ptr<Stage> pStage, DUNGEON_TYPE eDungeonType);
    FORCEINLINE shared_ptr<Stage> GetStage() { return std::move(m_pStage); }
    FORCEINLINE DUNGEON_TYPE GetDungeonType() { return m_eDungeonType; }

private:
    shared_ptr<Stage> m_pStage;
    DUNGEON_TYPE m_eDungeonType;
};

