#ifndef STATE_H
#define STATE_H
#include "userentity.h"

struct State
{
    bool isAuthenticated()
    {
        return currentUser.has_value();
    }

    void setCurrentUser(std::optional<UserEntity> user)
    {
        currentUser = user;
    }

    std::optional<UserEntity> getCurrentUser()
    {
        return currentUser;
    }

    private:
        std::optional<UserEntity> currentUser = std::nullopt;
};

#endif // STATE_H
