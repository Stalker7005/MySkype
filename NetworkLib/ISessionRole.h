#pragma once
namespace Network {
class ISessionRole
{
public:
    virtual void Invoke() = 0;
    virtual ~ISessionRole() {};
};

}


