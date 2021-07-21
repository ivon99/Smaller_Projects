#include <iostream>
#include <cstring>
#include <cmath>
#include "user.hpp"
#include "users_repository.hpp"
#include "challenge.hpp"
#include "challenges_repository.hpp"
using namespace std;
const int MAX_EMAIL_SIZE = 100;
const int MAX_TAG_SIZE = 32; //up to 31 + 1 for '\0'
const int MAX_SORT_SIZE = 20;

void clearCommand(char command[])
{
  for (int i = 0; i < 20; i++)
  {
    command[i] = ' ';
  }
}

char *inputEndless()
{
  int name_len = 10;
  char *name = new char[name_len];
  int iter = 0;
  char c;
  while ((c = cin.get()) != ' ')
  {
    name[iter] = c;
    if (iter == name_len - 1)
    {
      name_len *= 2;
      char *new_name = new char[name_len];
      strcpy(new_name, name);
      name = new_name;
    }
    iter++;
  }
  return name;
}

bool isaNum(char *input, int size)
{
  for (int i = 0; i < size; i++)
  {
    if ((input[i] >= '0') && (input[i] <= '9'))
      ;
    else
    {
      return false;
    }
  }
  return true;
}

int charToNum(char *input, int size)
{
  int number = 0;
  int digit;
  int exponent = -1;
  for (int i = size - 1; i >= 0; i--)
  {
    digit = input[i] - '0';
    exponent++;
    number += digit * pow(10, exponent);
  }
  return number;
}

int main()
{
  char command[20];
  command[0] = 'z';
  UsersRepository users;
  ChallengesRepository challenges;

  while (strcmp(command, "exit") != 0)
  {
    cin >> command;

    if (strcmp(command, "registration") == 0)
    {
      clearCommand(command);
      cin.get();
      //input: registration Ivan {19} {ivan@abv.bg}[space]
      char *name = inputEndless();
      char *input = new char[MAX_EMAIL_SIZE];
      char *email = new char[MAX_EMAIL_SIZE];
      int age = 0;
      bool email_inputted = false;
      cin.getline(input, MAX_EMAIL_SIZE, ' ');
      int size = strlen(input);
      if (isaNum(input, size))
      {
        age = charToNum(input, size);
        delete input;
      }
      else
      {
        strcpy(email, input);
        delete input;
        email_inputted = true;
      }
      if (!email_inputted)
      {
        if (cin.peek() != '\n')
        {
          cin.getline(email, MAX_EMAIL_SIZE, '\n');
          email_inputted = true;
        }
      }
      if (!email_inputted)
        strcpy(email, "unknown");

      User *new_user = new User(name, age, email);
      users.add(*new_user);

      continue;
    }

    if (strcmp(command, "challenge") == 0)
    {
      clearCommand(command);
      cin.get();
      //input:challenge user_name #challenge Name1[space]{Namer 2,Name 3(...)[space]}
      bool correct_in = true;
      char *name = inputEndless();
      char *challenge_tag = new char[MAX_TAG_SIZE];
      cin.getline(challenge_tag, MAX_TAG_SIZE, ' ');
      if (!users.isRegistered(name))
      {
        cout << "The user who is challenging is not registered" << endl;
        correct_in = false;
      }
      if (challenge_tag[0] != '#')
      {
        cout << "Error: Challenge tag must start with #!" << endl;
        correct_in = false;
      }

      if (correct_in)
      {
        while (cin.peek() != '\n')
        {
          char *name_challenged = inputEndless();
          if (strcmp(name_challenged, "unknown") == 0)
          {
            cout << "You cant challenge an unknown user" << endl;
            correct_in = false;
          }
          if (users.getUser(name)->challenge(challenge_tag, *users.getUser(name_challenged), users, challenges))
          {
            cout << users.getUser(name_challenged)->getName() << " was successfully challenged!" << endl;
          }
          else
          {
            cout << "Error: challenge not succesfull!" << endl;
          }
        }
      }

      continue;
    }

    if (strcmp(command, "finish") == 0)
    {
      clearCommand(command);
      cin.get();
      //input:finish #challenge user_id rating[space]
      bool correct_input = true;
      char *challenge_tag = new (nothrow) char[MAX_TAG_SIZE];
      if (!challenge_tag)
      {
        cout << "Error in memory allocation!" << endl;
        return 1;
      }
      cin.getline(challenge_tag, MAX_TAG_SIZE, ' ');
      unsigned int id_num;
      cin >> id_num;
      float rating;
      cin >> rating;

      if (challenge_tag[0] != '#')
      {
        cout << "Error: challenge tag must start with #!" << endl;
        correct_input = false;
      }
      if (!users.isRegisteredId(id_num))
      {
        cout << "Error: user with this ID number does not exist" << endl;
        correct_input = false;
      }
      if ((rating < -5.0) || (rating > 10.0))
      {
        cout << "Error: invalid input for rating" << endl;
        correct_input = false;
      }

      if (correct_input)
      {
        if (users.getUserByID(id_num)->finish(challenge_tag, rating, users, challenges))
        {
          cout << "Challenge finished!" << endl;
        }
        else
        {
          cout << "Error: challenge could not be finished!" << endl;
        }
      }

      continue;
    }

    if (strcmp(command, "profile_info") == 0)
    {
      clearCommand(command);
      cin.get();
      //input:profile_info name[space]
      char *name = inputEndless();
      users.getUser(name)->profile_info();

      continue;
    }

    if (strcmp(command, "list_by") == 0)
    {
      clearCommand(command);
      //input:list by newest/oldest/most_popular[space]
      char *sort_way = new char[MAX_SORT_SIZE];
      cin >> sort_way;
      challenges.list_by(sort_way);

      continue;
    }
  }

  return 0;
}