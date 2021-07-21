#ifndef _CHALLENGES_REPOSITORY_HPP_
#define _CHALLENGES_REPOSITORY_HPP_
#include "challenge.hpp"
#include "users_repository.hpp"

class ChallengesRepository
{
  static const int INITIAL_CAPACITY_CH = 10;
  Challenge *m_challengesrepo;
  int m_size;
  int m_capacity;

  void copyFrom(const ChallengesRepository &other);
  void resize(int);
  void selectionSort();

public:
  //-----The big 4:---
  ChallengesRepository();
  ChallengesRepository(int);
  ChallengesRepository(const ChallengesRepository &);
  ChallengesRepository &operator=(const ChallengesRepository &);
  ~ChallengesRepository();

  //getters
  int getSize() const;
  Challenge getChallengebyTag(const char *) const;
  int getIndexbyTag(const char *) const;

  //setters
  void setRatingbyTag(const char *tag, float rating);
  void setStatusbyTag(const char *tag);
  void setNumChallengedbyTag(const char *);

  //deletes
  void deleteByTag(const char *);

  void addChallenge(Challenge &); //++orderadded;
  bool isaChallenge(const char *);
  void list_by(const char *); //list by newest/oldest/most_popular
};

#endif