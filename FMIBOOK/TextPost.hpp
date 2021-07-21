#ifndef _TEXTPOST_HPP_
#define _TEXTPOST_HPP_
#include "IPost.hpp"

class TextPost : public IPost
{
private:
    char *m_text;
    int m_post_id;
    char* m_user;

private:
    void copyFrom(const TextPost &other);
    void writeTextToHTML(std::ofstream &outfile);

public:
    //==THE BIG 4===
    TextPost(const char *text = "no text",const char* username="unknown",int post_id = 0);
    TextPost(const TextPost &other);
    TextPost &operator=(const TextPost &other);
    ~TextPost();

    //==setters and getters
    virtual int getPostID() const override;
    virtual void setPostID(int post_id) override;
    virtual char* getPostUser() const override;

    //==file methods
    virtual void saveToHTML(const char *filename) override;
    virtual void saveToAppendHTML(std::ofstream &outfile) override;
};

#endif