#ifndef _NORMAL_USER_HPP_
#define _NORMAL_USER_HPP_
#include "User.hpp"

class NormalUser : public User
{
private:
    //char *m_nickname;
    //int m_age;
    //List<IPost *> m_own_post_repo;
    //bool m_blocked;
    
    void copyFrom(const NormalUser &other);

public:
    //==THE BIG 4==
    NormalUser(const char *nickname = "unknown user", int age = 0);
    NormalUser(const NormalUser &other);
    NormalUser &operator=(const NormalUser &other);
    ~NormalUser();

    //==overriden getters==
    virtual const char *getTypeOfUser() const override;
};

#endif