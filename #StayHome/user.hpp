#ifndef _USER_HPP_
#define _USER_HPP_
#include "challenges_repository.hpp"
#include "users_repository.hpp"

class UsersRepository;
class ChallengesRepository;

class User
{
  char *m_name;                          //dynamic
  unsigned int m_age;                    //do 90 godini
  char m_email[101];                     //do 100 simvola
  unsigned int m_idnumber;               //всеки потр има уникален, за да се различават при еднакви имена when registered
  ChallengesRepository *m_ownchallenges; //repo of own challenges

  void init(const char *, unsigned int, const char *);
  void clean();
  void copyFrom(const User &);

public:
  // The big 4
  User();
  User(const char *, unsigned int, const char *);
  User(const User &);
  User &operator=(const User &);
  ~User();

  //getters
  const char *getName() const;
  int getNumber() const;
  ChallengesRepository *getChallengesRepo();

  //setters
  void setIdNum(unsigned int);
  void setAge(unsigned int);

  //printing
  void profile_info() const;

  void addInOwnchallenges(Challenge &); //if challenged, the challenge is added to ownchallengesrepo
  bool challenge(char *tag_challenge, User &challenged, UsersRepository &users, ChallengesRepository &challenges);
  bool finish(const char *tag, float, UsersRepository &, ChallengesRepository &);
};

#endif