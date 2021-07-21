#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_
#include "User.hpp"

class Admin : public User
{
private:
    // char *m_nickname;
    // int m_age;
    // List<IPost *> m_own_post_repo;
    // bool m_blocked;

public:
    //==THE BIG 4==
    Admin(const char *nickname = "unknown", int age = 0);
    Admin(const User &other) = delete;
    Admin &operator=(const Admin &other) = delete;
    virtual ~Admin();

    //==overriden setters and getters==
    virtual const char *getTypeOfUser() const override;
    virtual void setBlockedStatus(bool status) override;

    //===overriden methods===
    virtual void removePost(User *user, int post_id) override;
    virtual void blockUser(User *other) override;
    virtual void unblockUser(User *other) override;
};

#endif