#include "Admin.hpp"
#include <iostream>
#include <cstring>
using namespace std;

Admin::Admin(const char *nickname, int age)
    : User(nickname, age)
{
    //cout << "Admin constructor called" << endl;
    ;
}

Admin::~Admin()
{
    //cout << "Admin destructor called" << endl;
    ;
}

const char *Admin::getTypeOfUser() const
{
    return "admin";
}

void Admin::setBlockedStatus(bool status)
{
    status = false;
    if (status == false)
    {
        cout << "Can't block an admin." << endl;
    }
}

void Admin::removePost(User *user, int post_id)
{
    user->User::removePost(user,post_id);  
}

void Admin::blockUser(User *other)
{
    other->setBlockedStatus(true);
    cout << other->getName() << " blocked." << endl;
}

void Admin::unblockUser(User *other)
{
    other->setBlockedStatus(false);
    cout << other->getName() << " unblocked." << endl;
}
