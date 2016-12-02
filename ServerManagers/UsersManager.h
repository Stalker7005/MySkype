#pragma once

namespace ServerManagers {

class UsersManager
{
public:
    void OnUserRegistration();
    void OnUserLogin();
    void OnUserLogout();
    void OnUserRemove();
};

}