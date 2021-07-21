#ifndef _USER_HPP_
#define _USER_HPP_
#include "List.hpp"
#include "IPost.hpp"

class User
{
  protected:
   char* m_nickname;
   int m_age;
   List<IPost*> m_own_post_repo;
   bool m_blocked;
  
  //==helper functions==
   void copyFrom(const User& other);
  
  public:
  //==THE BIG 4==
  User(const char* nickname="unknown", int age=0);
  User(const User& other);
  User& operator= (const User& other);
  virtual ~User();

  //==getters and setters==
  virtual const char* getTypeOfUser() const;
  virtual int getNumPosts() const;
  virtual int getIDPostAtIndex(int index) const;
  virtual int getAge() const;
  virtual bool getBlolckedStatus() const;
  virtual void setBlockedStatus(bool status);
  virtual void rename(const char* new_username);
  virtual const char* getName() const;

  //==methods==
  virtual void addPost(IPost* post);
  virtual void removePost(User* user,int post_id);
  virtual void blockUser(User* other);
  virtual void unblockUser(User* other);
  virtual void saveAllPostsToHTML(const char* filename) const;

};

#endif