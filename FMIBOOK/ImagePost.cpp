#include "ImagePost.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

//==helper functions==
void ImagePost::copyFrom(const ImagePost &other)
{
    m_image_filepath = new char[strlen(other.m_image_filepath) + 1];
    strcpy(m_image_filepath, other.m_image_filepath);
    m_user = new char[strlen(other.m_user) + 1];
    strcpy(m_user, other.m_user);
    m_post_id = other.m_post_id;
}

void ImagePost::writeImageToHTML(std::ofstream &outfile)
{
    outfile << "<!DOCTYPE html>" << endl;
    outfile << "<html>" << endl;
    outfile << "<body>" << endl;
    outfile << endl;
    outfile << "<h1>"
            << "Post #" << m_post_id << "</h1>" << endl;
    outfile << "<img src="
            << "\"" << m_image_filepath << "\""
            << ">" << endl;
    outfile << endl;
    outfile << "</body>" << endl;
    outfile << "</html>" << endl;
}

//==THE BIG 4===
ImagePost::ImagePost(const char *filepath, const char *username, int post_id)
{
    m_image_filepath = new char[strlen(filepath) + 1];
    strcpy(m_image_filepath, filepath);
    m_user = new char[strlen(username) + 1];
    strcpy(m_user, username);
    //m_post_id++;
    m_post_id = post_id;
}
ImagePost::ImagePost(const ImagePost &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}
ImagePost &ImagePost::operator=(const ImagePost &other)
{
    if (this != &other)
    {
        delete[] m_image_filepath;
        delete[] m_user;
        copyFrom(other);
    }
    return *this;
}
ImagePost::~ImagePost()
{
    delete[] m_image_filepath;
    delete[] m_user;
}

//==setters and getters
int ImagePost::getPostID() const
{
    return m_post_id;
}

void ImagePost::setPostID(int post_id)
{
    m_post_id = post_id;
}

char *ImagePost::getPostUser() const
{
    return m_user;
}

//==file methods==
void ImagePost::saveToHTML(const char *filename)
{
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile)
    {
        this->writeImageToHTML(outfile);
        cout<<"Successfully wrote image to file "<<filename<<" ."<<endl;
    }
    else
    {
        cout << "Unable to open file to save HTML" << endl;
    }
    outfile.close();
}

void ImagePost::saveToAppendHTML(std::ofstream &outfile)
{
    outfile << endl;
    outfile << "<h1>"
            << "Post #" << m_post_id << "</h1>" << endl;
    outfile << "<img src="
            << "\"" << m_image_filepath << "\""
            << ">" << endl;
    outfile << endl;
}
