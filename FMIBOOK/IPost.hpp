#ifndef _IPOST_HPP_
#define _IPOST_HPP_
#include <iostream>

class IPost
{
    public:
    virtual int getPostID() const = 0;
    virtual void setPostID(int post_id) =0;
    virtual char* getPostUser() const =0;
    virtual void saveToHTML(const char* filename) = 0;
    virtual void saveToAppendHTML(std::ofstream &outfile) =0 ;
    virtual ~IPost()
    {
        //std::cout << "Post destructor called" << std::endl;
        ;
    }
};

#endif