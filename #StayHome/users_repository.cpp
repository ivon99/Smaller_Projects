#include "users_repository.hpp"
#include "user.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void UsersRepository::copyFrom(const UsersRepository &other)
{
  m_size = other.m_size;
  m_capacity = other.m_capacity;
  m_usersrepo = new User[m_capacity];

  for (int i = 0; i < other.m_size; i++)
  {
    m_usersrepo[i] = other.m_usersrepo[i];
  }
}

void UsersRepository::resize(int new_capacity)
{
  User *tmp = new (nothrow) User[new_capacity];
  if (tmp)
  {
    for (int i = 0; i < m_size; i++)
    {
      tmp[i] = m_usersrepo[i];
    }
    delete[] m_usersrepo;
    m_capacity = new_capacity;
    m_usersrepo = tmp;
    //cout<<"UsersRepo was resized and now has a capacity of" << new_capacity<<endl;
  }
}

UsersRepository::UsersRepository() : m_size(0), m_capacity(INITIAL_CAPACITY)
{
  m_usersrepo = new User[INITIAL_CAPACITY];
  // cout<<"Default constructor users_repo called"<<endl;
}

UsersRepository::UsersRepository(int capacity) : m_size(0)
{
  m_capacity = capacity;
  m_usersrepo = new User[capacity];
  // cout<<"Constructor users_repo called"<<endl;
}

UsersRepository::UsersRepository(const UsersRepository &other)
{
  if (this != &other)
    copyFrom(other);
  // cout<<" Copy constructor users_repo called"<<endl;
}

UsersRepository &UsersRepository::operator=(const UsersRepository &other)
{
  if (this != &other)
  {
    delete[] m_usersrepo;
    copyFrom(other);
  }
  return *this;
  // cout<<"Operator = users_repo called"<<endl;
}

UsersRepository::~UsersRepository()
{
  delete[] m_usersrepo;
  //  cout<<"Users_repo destructor called"<<endl;
}

void UsersRepository::add(User &newUser)
{
  if (m_size == m_capacity)
  {
    resize(m_capacity * 2);
  }
  newUser.setIdNum(m_size);
  m_usersrepo[m_size] = newUser;
  m_size++;
  //cout<<"User added to repo of users and Idnumber set to ";
  newUser.getNumber();
}

bool UsersRepository::isRegistered(const char *username)
{
  for (int i = 0; i < m_size; i++)
  {
    const char *name = m_usersrepo[i].getName();
    if (strcmp(name, username) == 0)
      return true;
  }
  return false;
}

bool UsersRepository::isRegisteredId(unsigned int id_num)
{
  for (int i = 0; i < m_size; i++)
  {
    unsigned int num = m_usersrepo[i].getNumber();
    if (num == id_num)
      return true;
  }
  return false;
}

int UsersRepository::getSize() const
{
  return m_size;
}

User *UsersRepository::getUser(const char *user_name) const
{
  for (int i = 0; i < m_size; i++)
  {
    const char *name = m_usersrepo[i].getName();
    if (strcmp(name, user_name) == 0)
      return &m_usersrepo[i];
  }
  return nullptr;
}

User *UsersRepository::getUserByID(unsigned int id_num) const
{
  for (int i = 0; i < m_size; i++)
  {
    unsigned int num = m_usersrepo[i].getNumber();
    if (num == id_num)
      return &m_usersrepo[i];
  }
  return nullptr;
}