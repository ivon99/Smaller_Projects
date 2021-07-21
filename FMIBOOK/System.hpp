#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_
#include "IPost.hpp"
#include "ImagePost.hpp"
#include "LinkPost.hpp"
#include "TextPost.hpp"
#include "User.hpp"
#include "List.hpp" 
#include "NormalUser.hpp"
#include "Moderator.hpp"
#include "Admin.hpp"

class System
{
  List<User *> m_users;
  List<IPost *> m_posts;
  static int m_post_ID;

private:
//helper functions
  void clearCommand(char command[]);
  int isRegistered(char *name);
  int getPost(int post_ID);
  void addImagePost(char* actor,char *image_filepath, int index_actor);
  void addLinkPost(char *actor, char *url, int index_actor);
  void addTextPost(char *actor, char * text, int index_actor);

private: 
//methods
  void addUser(char *actor, char *type_to_add, char *subject, int age);
  void remove_user(char *actor, char *subject);
  void block(char *actor, char *subject);
  void unblock(char *actor, char *subject);
  void post(char *actor, char *type);
  void remove_post(char* actor,int post_id);
  void view_post(char* actor,int post_ID_input);
  void view_all_posts(char* actor,char* subject);
  void rename(char* actor,char* subject);
  void info() const;
  void help();

public:
  System() = default;
  System &operator=(const System &other) = delete;
  System(const System &other) = delete;
  ~System() = default;
  void run();
};

#endif