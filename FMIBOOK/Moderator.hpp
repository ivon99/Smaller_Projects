#ifndef _MODERATOR_HPP_
#define _MODERATOR_HPP_
#include "User.hpp"

class Moderator : public User
{
private:
    //char *m_nickname;
    //int m_age;
    //List<IPost *> m_own_post_repo;
    //bool m_blocked;
    
    void copyFrom(const Moderator &other);

public:
    //==THE BIG 4==
    Moderator(const char *nickname = "unknown moderator", int age = 0);
    Moderator(const Moderator &other);
    Moderator &operator=(const Moderator &other);
    ~Moderator();

    //==getters==
    virtual const char *getTypeOfUser() const override;
    
    //==overriden methods==
    virtual void removePost(User *user, int post_id) override;
    virtual void blockUser(User *other) override;
    virtual void unblockUser(User* other) override;
};

#endif