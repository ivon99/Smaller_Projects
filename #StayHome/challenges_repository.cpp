#include "challenges_repository.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void ChallengesRepository::copyFrom(const ChallengesRepository &other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_challengesrepo = new Challenge[m_capacity];

    for (int i = 0; i < other.m_size; i++)
    {
        m_challengesrepo[i] = other.m_challengesrepo[i];
    }
}

void ChallengesRepository::resize(int new_capacity)
{
    Challenge *tmp = new (nothrow) Challenge[new_capacity];
    if (tmp)
    {
        for (int i = 0; i < m_size; i++)
        {
            tmp[i] = m_challengesrepo[i];
        }
        delete[] m_challengesrepo;
        m_capacity = new_capacity;
        m_challengesrepo = tmp;
        //cout<<"ChallengesRepo was resized and now has a capacity of" << new_capacity<<endl;
    }
}

int ChallengesRepository::getSize() const
{
    return m_size;
}

ChallengesRepository::ChallengesRepository() : m_size(0), m_capacity(INITIAL_CAPACITY_CH)
{
    m_challengesrepo = new Challenge[INITIAL_CAPACITY_CH];
    //cout<<"Default Constructor challeng_repo called"<<endl;
}

ChallengesRepository::ChallengesRepository(int capacity) : m_size(0)
{
    m_capacity = capacity;
    m_challengesrepo = new Challenge[capacity];
    // cout<<"Constructor ch_repo called"<<endl;
}

ChallengesRepository::ChallengesRepository(const ChallengesRepository &other)
{
    if (this != &other)
        copyFrom(other);
    //cout<<"Copy Constructor ch_repo called"<<endl;
}

ChallengesRepository &ChallengesRepository::operator=(const ChallengesRepository &other)
{
    if (this != &other)
    {
        delete[] m_challengesrepo;
        copyFrom(other);
        // cout<<"Operator = ch_repo called"<<endl;
    }
    return *this;
}
ChallengesRepository::~ChallengesRepository()
{
    delete[] m_challengesrepo;
    // cout<<"Destructor ch_repo called"<<endl;
}

void ChallengesRepository::addChallenge(Challenge &new_challenge)
{
    // cout<<"Add challenge called!"<<endl;
    const char *tag_new_challenge = new_challenge.getTag();
    if (!isaChallenge(tag_new_challenge))
    {
        if (m_size == m_capacity)
        {
            // cout<<"Resizing"<<endl;
            resize(m_capacity * 2);
        }
        m_challengesrepo[m_size] = new_challenge;
        new_challenge.setOrderAdded(m_size);
        m_size++;
        //cout<<"Challenge added to repo of challenges"<<endl;
    }
}

bool ChallengesRepository::isaChallenge(const char *tag_ch)
{
    for (int i = 0; i < m_size; i++)
    {
        const char *tag = m_challengesrepo[i].getTag();
        if (strcmp(tag, tag_ch) == 0)
            return true;
    }
    return false;
}

Challenge ChallengesRepository::getChallengebyTag(const char *tag_ch) const
{
    for (int i = 0; i < m_size; i++)
    {
        const char *tag = m_challengesrepo[i].getTag();
        if (strcmp(tag, tag_ch) == 0)
            return m_challengesrepo[i];
    }
}

void ChallengesRepository::deleteByTag(const char *tag)
{
    int position = 0;
    for (int i = 0; i < m_size; i++)
    { //finds the position of the challenge
        const char *tag = m_challengesrepo[i].getTag();
        if (strcmp(tag, tag) == 0)
            position = 0;
    }

    if (position == m_size)
    { //if its the last element, make array smaller
        m_size--;
    }
    else
    {
        for (int i = position; i < m_size - 1; ++i)
        { //else rewrites it by shifting all elements one element on the left
            m_challengesrepo[i] = m_challengesrepo[i + 1];
        }
    }
    //cout<<"Deleted by tag!"<<endl;
}

void ChallengesRepository::selectionSort()
{
    int min_index = 0;
    for (int i = 0; i < m_size; i++)
    { //implementing selection sort for num_challenged
        min_index = i;
        for (int j = i + 1; j < m_size; j++)
        {
            if (m_challengesrepo[j].getNumCh() < m_challengesrepo[min_index].getNumCh())
            {
                min_index = j;
            }
        }
        Challenge tmp = m_challengesrepo[min_index];
        m_challengesrepo[min_index] = m_challengesrepo[i];
        m_challengesrepo[i] = tmp;
    }
}

void ChallengesRepository::list_by(const char *sorting)
{
    if (strcmp(sorting, "newest") == 0)
    {
        cout << "Challenges sorted by newest added:" << endl;
        for (int i = m_size - 1; i >= 0; i--)
        {
            m_challengesrepo[i].printChallenge();
        }
    }
    if (strcmp(sorting, "oldest") == 0)
    {
        cout << "Challenges sorted by oldest added:" << endl;
        for (int i = 0; i < m_size; i++)
        {
            m_challengesrepo[i].printChallenge();
        }
    }
    if (strcmp(sorting, "most_popular") == 0)
    {
        cout << "Challenges sorted by most popular:" << endl;
        this->selectionSort();
        for (int i = m_size - 1; i >= 0; i--)
        {
            m_challengesrepo[i].printChallenge();
        }
    }
}

int ChallengesRepository::getIndexbyTag(const char *tag) const
{
    for (int i = 0; i < m_size; i++)
    {
        const char *tag_this = m_challengesrepo[i].getTag();
        if (strcmp(tag_this, tag) == 0)
        {
            return i;
        }
    }
}

void ChallengesRepository::setRatingbyTag(const char *tag, float rating)
{
    int index;
    if (isaChallenge(tag))
    {
        index = getIndexbyTag(tag);
        m_challengesrepo[index].setRating(rating);
    }
    //cout<<"SetRating by tag called and the rating is set to"<<m_challengesrepo[index].getRating()<<endl;
}

void ChallengesRepository::setStatusbyTag(const char *tag)
{
    int index;
    if (isaChallenge(tag))
    {
        index = getIndexbyTag(tag);
        m_challengesrepo[index].setStatus();
    }
    //  cout<<"setStatus by tag called and the status is "<<m_challengesrepo[index].getStatus()<<endl;
}

void ChallengesRepository::setNumChallengedbyTag(const char *tag)
{
    int index;
    if (isaChallenge(tag))
    {
        index = getIndexbyTag(tag);
        m_challengesrepo[index].setNumChallenged();
    }
}
