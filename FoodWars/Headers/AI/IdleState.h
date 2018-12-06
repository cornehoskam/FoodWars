#ifndef PROJECT_SWA_IDLESTATE_H
#define PROJECT_SWA_IDLESTATE_H

#include "State.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/TurnComponent.h"

class IdleState : public State {
public:
    IdleState(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId);

    ~IdleState() override = default;

    void enter() override;

    void execute(double dt) override;

    void exit() override;
};

#endif //PROJECT_SWA_IDLESTATE_H
