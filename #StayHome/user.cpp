#include <cstring>
#include <iostream>
#include "user.hpp"
using namespace std;

void User::setAge(unsigned int age)
{
    if ((age >= 0) && (age < 91))
        m_age = age;
    else
    {
        std::cout << "Age should be below 91 years!" << std::endl;
        m_age = 0;
    }
}

void User::setIdNum(unsigned int num)
{
    m_idnumber = num;
    //cout<<"Setting id num to " <<num<<endl;
}

const char *User::getName() const
{
    return m_name;
}

int User::getNumber() const
{
    return m_idnumber;
}

ChallengesRepository *User::getChallengesRepo()
{
    return m_ownchallenges;
}

void User::init(const char *name, unsigned int age, const char *email)
{
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
    this->setAge(age);
    strcpy(m_email, email);
    m_ownchallenges = new ChallengesRepository;
}

void User::clean()
{
    delete[] m_name;
    delete m_ownchallenges;
}

void User::copyFrom(const User &other)
{
    m_name = new char[strlen(other.m_name) + 1];
    strcpy(m_name, other.m_name);
    this->setAge(other.m_age);
    strcpy(m_email, other.m_email);
    m_ownchallenges = new ChallengesRepository;
    m_ownchallenges = other.m_ownchallenges;
    m_idnumber = other.m_idnumber;
}

User::User() : m_idnumber(0), m_ownchallenges(nullptr)
{
    init("unknown", 0, "unknown");
    //std::cout<<"Defaut constructor called user.Name: " << m_name << ", Age:" << m_age <<", Email: "<<m_email<<std::endl;
}

User::User(const char *name, unsigned int age = 0, const char *email = "unknown") : m_idnumber(0), m_ownchallenges(nullptr)
{
    init(name, age, email);
    //std::cout<<"Constructor called for user.Name: " << m_name << ", Age:" << m_age <<", Email: "<<m_email<<std::endl;
}

User::User(const User &other)
{
    if (this != &other)
    {
        copyFrom(other);
        // cout<<"Copy constructor user called."<<endl;
    }
}

User &User::operator=(const User &other)
{
    if (this != &other)
    {
        clean();
        copyFrom(other);
        // cout<<"Operator = called user."<<endl;
    }
    return *this;
}

User::~User()
{
    clean();
}

void User::addInOwnchallenges(Challenge &challenge)
{
    m_ownchallenges->addChallenge(challenge);
    //cout<<challenge.getTag()<<" added to own challenges."<<endl;
}

bool User::challenge(char *tag_challenge, User &challenged, UsersRepository &users, ChallengesRepository &challenges)
{
    if (!users.isRegistered(challenged.getName()))
    {
        std::cout << "Error: Challenged user is not registered" << std::endl;
        return false;
    }
    //cout<<"Challenged user is registered"<<endl;

    if (!challenges.isaChallenge(tag_challenge))
    {                                                                      //if challenge is not registered
        Challenge *new_challenge = new (nothrow) Challenge(tag_challenge); //making a new challenge
        if (!new_challenge)
        {
            cout << "Failed memory allocation for challenge" << endl;
            return false;
        }
        else
        {
            challenges.addChallenge(*new_challenge);         //adding challenge to challenge repo
            challenges.setNumChallengedbyTag(tag_challenge); //++num challenged
            challenges.setStatusbyTag(tag_challenge);        //setting status
            challenged.addInOwnchallenges(*new_challenge);   //adding challenge to challenged users ownrepo
            //cout<<"Challenge was added to "<< challenged.getName()<<"'s repo"<<endl;
            return true;
        }
    }
    else
    { //already an existing challenge-> adds it to repo and changes the status and num_challenged
        Challenge challenge = challenges.getChallengebyTag(tag_challenge);
        challenged.addInOwnchallenges(challenge);
        challenges.setNumChallengedbyTag(tag_challenge); //++num challenged
        challenges.setStatusbyTag(tag_challenge);        //setting status
        //cout<<"Challenge was added to "<< challenged.getName()<<"'s repo"<<endl;
        return true;
    }
}

bool User::finish(const char *tag, float rating, UsersRepository &users, ChallengesRepository &challenges)
{
    if (!m_ownchallenges->isaChallenge(tag))
    {
        cout << "Not able to find a challenge with this tag. " << endl;
        return false;
    }
    challenges.setRatingbyTag(tag, rating);
    m_ownchallenges->deleteByTag(tag); //deletes the challenge from user's challenges repo
    return true;
}

void User::profile_info() const
{
    std::cout << "Name: " << m_name << endl;
    cout << "Age: " << m_age << endl;
    cout << "Email: " << m_email << endl;
    cout << "ID number: " << m_idnumber << endl;
}
