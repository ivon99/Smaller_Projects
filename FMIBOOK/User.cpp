#include "User.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

//==helper functions==
void User::copyFrom(const User &other)
{
    m_nickname = new char[strlen(other.m_nickname) + 1];
    strcpy(m_nickname, other.m_nickname);
    m_age = other.m_age;
    m_own_post_repo = other.m_own_post_repo;
    m_blocked = other.m_blocked;
}

//==THE BIG 4==
User::User(const char *nickname, int age)
{
    m_nickname = new char[strlen(nickname) + 1];
    strcpy(m_nickname, nickname);
    if ((age > 100) || (age < 0))
    {
        cout << "Errror: age should be between 0 and 100 years. Age set to 0." << endl;
        m_age=0;
    }
    else
    {
        m_age = age;
    }
    m_own_post_repo = List<IPost *>();
    m_blocked = false;
}
User::User(const User &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}
User &User::operator=(const User &other)
{
    if (this != &other)
    {
        delete[] m_nickname;
        copyFrom(other);
    }
    return *this;
}
User::~User()
{
    delete[] m_nickname;
    //cout << "User destructor called" << endl;
}

//==setters and getters==
const char *User::getTypeOfUser() const
{
    return "Unspecified User";
}

int User::getIDPostAtIndex(int index) const
{
   return m_own_post_repo[index]->getPostID();
}

int User::getNumPosts() const
{
    return m_own_post_repo.getSize();
}

int User::getAge() const
{
    return m_age;
}

bool User::getBlolckedStatus() const
{
    return m_blocked;
}

void User::rename(const char *new_username)
{
     cout<<"User "<<m_nickname;
    delete[] m_nickname;
    m_nickname = new char[strlen(new_username) + 1];
    strcpy(m_nickname, new_username);
    cout<<" is now known as "<<m_nickname<<" ."<<endl;
}

void User::setBlockedStatus(bool status)
{
    m_blocked = status;
}

const char *User::getName() const
{
    return m_nickname;
}
//==common methods==
void User::addPost(IPost *post)
{
    if(m_blocked==false)
    {
    m_own_post_repo.addElement(post);
    }
    else
    {
        cout<<"Blocked user can't post new posts!"<<endl;
    }
}

//==specific methods==
void User::removePost(User *user, int post_id)
{
    if (this == user)
    {
        int num_posts= m_own_post_repo.getSize();
        int index_post = -1;
        for(int i=0;i<num_posts;i++)
        {
            if(m_own_post_repo[i]->getPostID()==post_id)
            {
                index_post=i;
                break;
            }
        }
        if(index_post>=0)
        {
        m_own_post_repo.deleteElement(index_post);
        cout<<m_nickname<<"'s post removed."<<endl;
        return;
        }
        else
        {
            cout<<"Unable to remove post with id "<<post_id<<endl;
            return;
        }
    }
    else
    {
        cout << "Error: user of type " << this->getTypeOfUser() << " has no persmission to remove "
             << user->getName() << "'s posts!" << endl;
             return;
    }
}

void User::blockUser(User *other)
{
    cout << "Error: user of type " << this->getTypeOfUser() << " has no persmission to block " << other->getName() << endl;
}

void User::unblockUser(User *other)
{
    cout << "Error: user of type " << this->getTypeOfUser() << " has no persmission to block " << other->getName() << endl;
}

//==file methods==
void User::saveAllPostsToHTML(const char *filename) const
{
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::app);
    if (outfile)
    {
        outfile << "<!DOCTYPE html>" << endl;
        outfile << "<html>" << endl;
        outfile << "<body>" << endl;
        int size = m_own_post_repo.getSize();
        for (int i = 0; i < size; i++)
        {
            m_own_post_repo[i]->saveToAppendHTML(outfile);
        }
        outfile << "</body>" << endl;
        outfile << "</html>" << endl;
        cout<<"Successfully wrote a file with all the posts of "<<m_nickname<<" at "<<filename<<" ."<<endl; 
    }
    else
    {
        cout << "Unable to open file to save HTML" << endl;
    }
    outfile.close();
}
