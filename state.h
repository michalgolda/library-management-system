#ifndef STATE_H
#define STATE_H
#include "userentity.h"

struct State
{
    std::optional<UserEntity> currentUser = std::nullopt;

    bool isAuthenticated()
    {
        return currentUser.has_value();
    }
};

#endif // STATE_H
