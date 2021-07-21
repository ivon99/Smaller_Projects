#ifndef _CHALLENGE_HPP_
#define _CHALLENGE_HPP_

class Challenge
{ //represented under 40 bytes
  static const int MAX_TAG_SIZE = 31;
  static const int MAX_STATUS_SIZE = 20;
  char *m_tag;                        //уникално, започва с # и е до 31 символа ???
  char *m_status;                     //0--new, 2-10 --quite recently, >11-- old
  unsigned short int m_numchallenged; //up to 65535
  float m_rating;                     // [-5.00,10.0]
  int m_orderadded;                   //used for listing

  void copyFrom(const Challenge &other);
  void clean();

public:
  //The big 4
  Challenge();
  Challenge(char *);
  Challenge(const Challenge &);
  Challenge &operator=(const Challenge &);
  ~Challenge();

  //setters
  bool setTag(char *);
  void setOrderAdded(int);
  void setStatus();        //changes status:{new,quite recently,old}
  void setNumChallenged(); //changes num challenged
  void setRating(float new_rating);

  //getters
  const char *getTag();
  unsigned short int getNumCh() const;
  const char *getStatus() const;
  float getRating() const;
  void printChallenge() const;
};

#endif