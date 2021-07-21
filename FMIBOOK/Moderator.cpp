#include "Moderator.hpp"
#include <cstring>
#include <iostream>
using namespace std;

//==helper functions==
void Moderator::copyFrom(const Moderator &other)
{
    m_nickname = new char[strlen(other.m_nickname) + 1];
    strcpy(m_nickname, other.m_nickname);
    m_age = other.m_age;
    m_own_post_repo = other.m_own_post_repo;
    m_blocked = other.m_blocked;
}

//==THE BIG 4==
Moderator::Moderator(const char *username, int age)
    : User(username, age)
{
   cout <<"Moderator "<< username<<" created."<< endl;
}

Moderator::Moderator(const Moderator &other)
:User()
{
    if (this != &other)
    {
        copyFrom(other);
    }
}

Moderator &Moderator::operator=(const Moderator &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

Moderator::~Moderator()
{
    ;
    //cout << "Moderator destructor called" << endl;
}

//==getters==
const char *Moderator::getTypeOfUser() const
{
    return "moderator";
}

//==overriden methods==
void Moderator::removePost(User* user,int post_id)  
{
    user->User::removePost(user,post_id); 
}

void Moderator::blockUser(User* other)
{
  other->setBlockedStatus(true);
  cout<<other->getName()<<" blocked."<<endl;
}

void Moderator::unblockUser(User* other)
{
    other->setBlockedStatus(false);
    cout<<other->getName()<<" unblocked."<<endl;
}