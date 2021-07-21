#include <iostream>
#include <fstream>
#include <cstring>
#include "TextPost.hpp"
using namespace std;

//==helper functions
void TextPost::copyFrom(const TextPost &other)
{
    m_text = new char[strlen(other.m_text) + 1];
    stpcpy(m_text, other.m_text);
    m_user= new char[strlen(other.m_user)+1];
    strcpy(m_user, other.m_user);
    m_post_id=other.m_post_id;
}

void TextPost::writeTextToHTML(std::ofstream &outfile)
{
    outfile << "<!DOCTYPE html>" << endl;
    outfile << "<html>" << endl;
    outfile << "<body>" << endl;
    outfile << endl;
    outfile << "<h1>"<< "Post #" << m_post_id << "</h1>" << endl;
    outfile << "<p>"<< m_text <<"</p>"<< endl;
    outfile << endl;
    outfile << "</body>" << endl;
    outfile << "</html>" << endl;
}

//==THE BIG 4===
TextPost::TextPost(const char *text,const char* username,int post_id)
{
    m_text = new char[strlen(text) + 1];
    stpcpy(m_text, text);
    m_user= new char[strlen(text)+1];
    strcpy(m_user,username);
    //m_post_id++;
    m_post_id=post_id;
}
TextPost::TextPost(const TextPost &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}
TextPost &TextPost::operator=(const TextPost &other)
{
    if (this != &other)
    {
        delete[] m_text;
        delete[] m_user;
        copyFrom(other);
    }
    return *this;
}
TextPost::~TextPost()
{
    delete[] m_text;
    delete[] m_user;
}

//==setters and getters
int TextPost::getPostID() const
{
    return m_post_id;
}

void TextPost::setPostID(int post_id)
{
   m_post_id=post_id;
}

char* TextPost::getPostUser() const
{
   return m_user;
}

//==file methods
void TextPost::saveToHTML(const char *filename)
{
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile)
    {
        this->writeTextToHTML(outfile);
        cout<<"Succesfully wrote text to file "<<filename<<" ."<<endl;
    }
    else
    {
        cout << "Unable to open file to save HTML" << endl;
    }
    outfile.close();
}

void TextPost::saveToAppendHTML(std::ofstream &outfile) 
{
    outfile << endl;
    outfile << "<h1>"<< "Post #" << m_post_id << "</h1>" << endl;
    outfile << "<p>"<< m_text <<"</p>"<< endl;
    outfile << endl;
}