#include "DBClientsManagmentHelper.h"
namespace ServerManagment {
DBClientsManagmentHelper::DBClientsManagmentHelper()
{

}

ServerManagment::DBClientsManagmentHelper& DBClientsManagmentHelper::GetInstance()
{
    static DBClientsManagmentHelper helper;

    return helper;
}

DBClientsManagmentHelper::~DBClientsManagmentHelper()
{

}
}

