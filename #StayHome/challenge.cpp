#include <iostream>
#include <cstring>
using namespace std;
#include "challenge.hpp"

bool Challenge::setTag(char *tag)
{
  if (tag[0] != '#')
  {
    std::cout << "Challenge tag must start with a '#'!" << std::endl;
    return false;
  }
  else
  {
    strcpy(m_tag, tag);
    //  cout<<"tag is set to"<< m_tag;
    return true;
  }
}

const char *Challenge::getTag()
{
  return m_tag;
}

unsigned short int Challenge::getNumCh() const
{
  return m_numchallenged;
}

void Challenge::setNumChallenged()
{
  m_numchallenged++;
  //cout<<"Ive updated num challenged to"<< m_numchallenged<<endl;
}

void Challenge::setStatus()
{
  if (m_numchallenged < 2)
  {
    strcpy(m_status, "new");
    // cout<<"Challenge status is updated to "<<m_status<<endl;
  }
  if ((m_numchallenged >= 2) && (m_numchallenged < 11))
  {
    strcpy(m_status, "quite recently");
    // cout<<"Challenge status is updated to "<<m_status<<endl;
  }
  if (m_numchallenged >= 11)
  {
    strcpy(m_status, "old");
    // cout<<"Challenge status is updated to "<<m_status<<endl;
  }
}

void Challenge::setRating(float new_rating)
{
  if (m_rating == 0)
  {
    m_rating = new_rating;
  }
  else
  {
    m_rating = (m_rating + new_rating) / 2;
  }
  // cout<<"Rating is set to "<< m_rating<<endl;
}

void Challenge::copyFrom(const Challenge &other)
{
  m_tag = new (nothrow) char[MAX_TAG_SIZE];
  if (!m_tag)
    cout << "Memory allocation error!" << endl;
  strcpy(m_tag, other.m_tag);
  m_status = new (nothrow) char[MAX_STATUS_SIZE];
  if (!m_status)
    cout << "Bad memory allocation!" << endl;
  strcpy(m_status, other.m_status);
  m_numchallenged = other.m_numchallenged;
  m_rating = other.m_rating;
  m_orderadded = other.m_orderadded;
}

void Challenge::clean()
{
  delete[] m_tag;
  delete[] m_status;
}
Challenge::Challenge() : m_numchallenged(0), m_rating(0), m_orderadded(0)
{
  m_tag = new char[MAX_TAG_SIZE];
  strcpy(m_tag, "#unknown");
  m_status = new char[MAX_STATUS_SIZE];
  strcpy(m_status, "new");
  // cout<<"Default constructor challenge called with tag "<<m_tag<<endl;
}

Challenge::Challenge(char *tag) : m_numchallenged(0), m_rating(0), m_orderadded(0)
{
  m_tag = new char[MAX_TAG_SIZE];
  bool good = setTag(tag);
  if (!good)
  {
    std::cout << "Error inputting tag, tag is set to default!" << std::endl;
    strcpy(m_tag, "#unknown");
  }
  m_status = new char[MAX_STATUS_SIZE];
  strcpy(m_status, "new");
  // cout<<"Constructor challenge called with tag "<<m_tag<<endl;
}

Challenge::Challenge(const Challenge &other)
{
  if (this != &other)
  {
    copyFrom(other);
  }
  //cout<<"Copy constructor challenge called with tag "<<m_tag<<endl;
  //cout<<m_tag<<" "<<m_status<<" "<<m_numchallenged<<" "<<m_rating<<endl;
}

Challenge &Challenge::operator=(const Challenge &other)
{
  if (this != &other)
  {
    this->clean();
    copyFrom(other);
  }
  return *this;
  //cout<<"Operator = challenge called with tag"<<m_tag<<endl;
}

Challenge::~Challenge()
{
  clean();
}

void Challenge::setOrderAdded(int num)
{
  m_orderadded = num;
}

float Challenge::getRating() const
{
  return m_rating;
}

const char *Challenge::getStatus() const
{
  return m_status;
}

void Challenge::printChallenge() const
{
  cout << "Challenge tag:" << m_tag << endl;
  cout << "Challenge status:" << m_status << endl;
  cout << "Number challenged: " << m_numchallenged << endl;
  cout << "Rating: " << m_rating << endl;
}