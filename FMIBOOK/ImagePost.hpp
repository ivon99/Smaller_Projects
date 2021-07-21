#ifndef _IMAGEPOST_HPP_
#define _IMAGEPOST_HPP_
#include "IPost.hpp"

class ImagePost : public IPost
{
private:
    char *m_image_filepath;
    int m_post_id;
    char* m_user;

private:
    void copyFrom(const ImagePost &other);
    void writeImageToHTML(std::ofstream &outfile);

public:
    //==THE BIG 4===
    ImagePost(const char *filepath = "unknown", const char* username="unkown",int post_id=0);
    ImagePost(const ImagePost &other);
    ImagePost &operator=(const ImagePost &other);
    ~ImagePost();

    //==setters and getters
    virtual int getPostID() const override;
    virtual void setPostID(int post_id) override;
    virtual char* getPostUser() const override;

    //==file methods
    virtual void saveToHTML(const char *filename) override;
    virtual void saveToAppendHTML(std::ofstream &outfile) override;
};
#endif