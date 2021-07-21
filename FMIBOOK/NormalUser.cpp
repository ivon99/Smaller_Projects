#include "NormalUser.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void NormalUser::copyFrom(const NormalUser &other)
{
    m_nickname = new char[strlen(other.m_nickname) + 1];
    strcpy(m_nickname, other.m_nickname);
    m_age = other.m_age;
    m_own_post_repo = other.m_own_post_repo;
    m_blocked = other.m_blocked;
}

//==THE BIG 4==
NormalUser::NormalUser(const char *username, int age)
    : User(username, age)
{
    cout <<"User "<< username<<" created."<< endl;
}

NormalUser::NormalUser(const NormalUser &other)
    : User()
{
    if (this != &other)
    {
        copyFrom(other);
    }
    cout << "NormalUser copy constructor called" << endl;
}

NormalUser &NormalUser::operator=(const NormalUser &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    cout << "Operator = normal user called" << endl;
    return *this;
}
NormalUser::~NormalUser()
{
    cout << "NormalUser destructor called" << endl;
}

//==setters and getters
const char *NormalUser::getTypeOfUser() const
{
    return "normal user";
}
