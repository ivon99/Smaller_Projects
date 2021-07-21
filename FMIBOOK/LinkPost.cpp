#include <iostream>
#include <fstream>
#include <cstring>
#include "LinkPost.hpp"
using namespace std;

void LinkPost::copyFrom(const LinkPost &other)
{
    m_url = new char[strlen(other.m_url) + 1];
    stpcpy(m_url, other.m_url);
    m_url_description = new char[strlen(other.m_url_description) + 1];
    strcpy(m_url_description, other.m_url_description);
    m_user = new char[strlen(other.m_user) + 1];
    strcpy(m_user, other.m_user);
    m_post_id = other.m_post_id;
}

void LinkPost::clear()
{
    delete[] m_url;
    delete[] m_url_description;
    delete[] m_user;
}

void LinkPost::writeLinkToHTML(std::ofstream &outfile)
{
    outfile << "<!DOCTYPE html>" << endl;
    outfile << "<html>" << endl;
    outfile << "<body>" << endl;
    outfile << endl;
    outfile << "<h1>"
            << "Post #" << m_post_id << "</h1>" << endl;
    outfile << "<p><a href="
            << "\"" << m_url << "\""
            << ">" << m_url_description << "</a></p>" << endl;
    outfile << endl;
    outfile << "</body>" << endl;
    outfile << "</html>" << endl;
}

//==THE BIG 4===
LinkPost::LinkPost(const char *url, const char *url_description, const char *username, int post_id)
{
    m_url = new char[strlen(url) + 1];
    stpcpy(m_url, url);
    m_url_description = new char[strlen(url_description) + 1];
    strcpy(m_url_description, url_description);
    m_user = new char[strlen(username) + 1];
    strcpy(m_user, username);
    m_post_id = post_id;
}
LinkPost::LinkPost(const LinkPost &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}
LinkPost &LinkPost::operator=(const LinkPost &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }
    return *this;
}
LinkPost::~LinkPost()
{
    clear();
}

//==setters and getters
int LinkPost::getPostID() const
{
    return m_post_id;
}

void LinkPost::setPostID(int post_id)
{
    m_post_id = post_id;
}

char *LinkPost::getPostUser() const
{
    return m_user;
}

//==file methods
void LinkPost::saveToHTML(const char *filename)
{
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile)
    {
        this->writeLinkToHTML(outfile);
        cout<<"Successfully wrote link to file "<<filename<<" ."<<endl;
    }
    else
    {
        cout << "Unable to open file to save HTML" << endl;
    }
    outfile.close();
}

void LinkPost::saveToAppendHTML(std::ofstream &outfile)
{
    outfile << endl;
    outfile << "<h1>"
            << "Post #" << m_post_id << "</h1>" << endl;
    outfile << "<p><a href="
            << "\"" << m_url << "\""
            << ">" << m_url_description << "</a></p>" << endl;
    outfile << endl;
}