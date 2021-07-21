#ifndef _USERS_REPOSITORY_HPP_
#define _USERS_REPOSITORY_HPP_
#include "user.hpp"

class User;

class UsersRepository
{
   static const int INITIAL_CAPACITY = 10;
   User *m_usersrepo; //list of users
   int m_size;
   int m_capacity;

   //helper funcstions:
   void copyFrom(const UsersRepository &);
   void resize(int);

public:
   //---The big 4--
   UsersRepository();
   UsersRepository(int);
   UsersRepository(const UsersRepository &other);
   UsersRepository &operator=(const UsersRepository &other);
   ~UsersRepository();

   //getters
   User *getUser(const char *) const;
   User *getUserByID(unsigned int) const;
   int getSize() const;

   void add(User &newUser);
   bool isRegistered(const char *);
   bool isRegisteredId(unsigned int);
};

#endif