#ifndef _LINKPOST_HPP_
#define _LINKPOST_HPP_
#include "IPost.hpp"

class LinkPost : public IPost
{
private:
    char *m_url;
    char *m_url_description;
    int m_post_id;
    char* m_user;

private:
    void copyFrom(const LinkPost &other);
    void clear();
    void writeLinkToHTML(std::ofstream &outfile);

public:
    //==THE BIG 4===
    LinkPost(const char *url = "unknown", const char *url_description = "link",const char* username="unknown", int post_id=0);
    LinkPost(const LinkPost &other);
    LinkPost &operator=(const LinkPost &other);
    ~LinkPost();

    //==setters and getters
    virtual int getPostID() const override;
    virtual void setPostID(int post_id) override;
    virtual char* getPostUser() const override;

    //==file methods
    virtual void saveToHTML(const char *filename) override;
    virtual void saveToAppendHTML(std::ofstream &outfile) override;
};

#endif