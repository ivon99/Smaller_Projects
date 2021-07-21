#include "System.hpp"
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_COMMAND_SIZE = 50;
const int MAX_USERNAME_SIZE = 100;
const int MAX_FILEPATH_SIZE = 50;
const int MAX_URL_SIZE = 2000;
const int MAX_URL_DESCRIPTION_SIZE = 2000;
const int MAX_INPUT_TEXT_SIZE = 2000;
const int MAX_NUM = 2147483647;

int System::m_post_ID = 0;

//===char manipulation helper functions===
char *concatanate(const char *first, const char *second)
{
    int size_first = strlen(first);
    int size_second = strlen(second);

    char *full = new char[size_first + size_second + 1];

    int index_full = 0;
    for (index_full = 0; index_full < size_first; index_full++)
    {
        full[index_full] = first[index_full];
    }

    for (int j = 0; j < size_second; j++)
    {
        full[index_full] = second[j];
        index_full++;
    }

    full[index_full] = '\0';
    //cout << full << endl;
    return full;
}

char *intToChar(int num)
{
    int tmp = num;
    int ctr = 0;
    while (tmp > 0)
    {
        tmp = tmp / 10;
        ctr++;
    }
    if (ctr == 0)
    {
        char *ch = new char[2];
        ch[0] = tmp + '0';
        ch[1] = '\0';
        return ch;
    }
    tmp = num;
    char *char_num = new char[MAX_NUM];
    int num_index = ctr - 1;
    while (tmp != 0)
    {
        int digit = tmp % 10;
        char digit_ch = digit + '0';
        tmp /= 10;
        char_num[num_index] = digit_ch;
        num_index--;
    }
    char_num[ctr] = '\0';
    return char_num;
}

//===system helper functions===
/*returns index of registred user in system */
int System::isRegistered(char *name)
{
    int size = m_users.getSize();
    for (int i = 0; i < size; i++)
    {
        const char *name_at_index = m_users[i]->getName();
        if (strcmp(name, name_at_index) == 0)
        {
            return i;   
        }
    }
    return -1;
}

int System::getPost(int post_ID)
{
    int size = m_posts.getSize();
    for (int i = 0; i < size; i++)
    {
        if (m_posts[i]->getPostID() == post_ID)
        {
            return i;
        }
    }
    return -1;
}

void System::addImagePost(char *actor, char *image_filepath, int index_actor)
{
    IPost *image_post = new ImagePost(image_filepath, actor, m_post_ID);
    m_users[index_actor]->addPost(image_post);
    if (m_users[index_actor]->getBlolckedStatus() == false)
    {
        m_posts.addElement(image_post);
        cout << "Post with post_id " << m_post_ID << " created." << endl;
        m_post_ID++;
        return;
    }
    else
    {
        return;
    }
}

void System::addLinkPost(char *actor, char *url, int index_actor)
{
    char *description = new char[MAX_URL_DESCRIPTION_SIZE];
    cin.getline(description, MAX_URL_DESCRIPTION_SIZE);
    IPost *link_post = new LinkPost(url, description, actor, m_post_ID);
    m_users[index_actor]->addPost(link_post);
    if (m_users[index_actor]->getBlolckedStatus() == false)
    {
        m_posts.addElement(link_post);
        cout << "Post with post_id " << m_post_ID << " created." << endl;
        m_post_ID++;
        return;
    }
    else
    {
        return;
    }
}

void System::addTextPost(char *actor, char *text, int index_actor)
{
    IPost *text_post = new TextPost(text, actor, m_post_ID);
    m_users[index_actor]->addPost(text_post);
    if (m_users[index_actor]->getBlolckedStatus() == false)
    {
        m_posts.addElement(text_post);
        cout << "Post with post_id " << m_post_ID << " created." << endl;
        m_post_ID++;
        return;
    }
    else
    {
        return;
    }
}

//===methods===
void System::addUser(char *actor, char *type_to_add, char *subject, int age)
{
    int index_actor = isRegistered(actor);
    if (isRegistered(subject) >= 0)
    {
        cout << "User with this username already exists." << endl;
        return;
    }
    if (index_actor >= 0)
    {
        const char *type = m_users[index_actor]->getTypeOfUser();
        if (strcmp(type, "admin") == 0)
        {
            if (strcmp(type_to_add, "moderator") == 0)
            {
                User *new_moderator = new Moderator(subject, age);
                m_users.addElement(new_moderator);
                return;
            }
            if (strcmp(type_to_add, "user") == 0)
            {
                User *new_user = new NormalUser(subject, age);
                m_users.addElement(new_user);
                return;
            }
            if (strcmp(type_to_add, "admin") == 0)
            {
                cout << "Error: only one admin exists." << endl;
                return;
            }
            else
            {
                cout << "User type not recognised!" << endl;
                return;
            }
        }
        else
        {
            cout << "User is not admin and can't add users!" << endl;
            return;
        }
    }
    else
    {
        cout << "User adding is not registered" << endl;
        return;
    }
}

void System::remove_user(char *actor, char *subject)
{
    int index_actor = isRegistered(actor);
    if (index_actor >= 0)
    {
        const char *type = m_users[index_actor]->getTypeOfUser();
        if (strcmp(type, "admin") == 0)
        {
            int index_subject = isRegistered(subject);
            if (index_subject >= 0)
            {
                //deletes all of the users posts in the system
                int num_posts_subject = m_users[index_subject]->getNumPosts();
                int post_id = 0;
                int post_index = 0;
                for (int i = num_posts_subject - 1; i >= 0; i--)
                {
                    post_id = m_users[index_subject]->getIDPostAtIndex(i); //locates all post id's the subject has made
                    post_index = getPost(post_id);                         //gives the index of post in system list with the given post id
                    m_posts.deleteElement(post_index);                     //deletes posts at given indexes from system
                }

                //deletes user from list of users
                m_users.deleteElement(index_subject);

                cout << subject << " removed." << endl;
                return;
            }
            else
            {
                cout << "User to remove is not registered!" << endl;
                return;
            }
        }
        else
        {
            cout << "User is not admin and can't remove users!" << endl;
            return;
        }
    }
    else
    {
        cout << "User is not registered!" << endl;
        return;
    }
}

void System::block(char *actor, char *subject)
{
    int index_actor = isRegistered(actor);
    int index_subject = isRegistered(subject);
    if ((index_actor >= 0) && (index_subject >= 0))
    {
        m_users[index_actor]->blockUser(m_users[index_subject]);
        return;
    }
    else
    {
        cout << "User is not registered!" << endl;
        return;
    }
}

void System::unblock(char *actor, char *subject)
{
    int index_actor = isRegistered(actor);
    int index_subject = isRegistered(subject);
    if ((index_actor >= 0) && (index_subject >= 0))
    {
        m_users[index_actor]->unblockUser(m_users[index_subject]);
        return;
    }
    else
    {
        cout << "User is not registered!" << endl;
        return;
    }
}

void System::post(char *actor, char *type)
{
    char *input = new char[MAX_INPUT_TEXT_SIZE];
    int index_actor = isRegistered(actor);
    if (index_actor >= 0)
    {
        if (strcmp(type, "image") == 0)
        {
            cin >> input;
            addImagePost(actor, input, index_actor);
            return;
        }
        if (strcmp(type, "url") == 0)
        {
            cin >> input;
            addLinkPost(actor, input, index_actor);
            return;
        }
        if (strcmp(type, "text") == 0)
        {
            cin.getline(input, MAX_INPUT_TEXT_SIZE);
            addTextPost(actor, input, index_actor);
            return;
        }
        else
        {
            cout << "Invalid type of post!" << endl;
            cin.getline(input, MAX_INPUT_TEXT_SIZE);
            return;
        }
    }
    else
    {
        cout << "User is not registered!" << endl;
        cin.getline(input, MAX_INPUT_TEXT_SIZE);
        return;
    }
}

void System::remove_post(char *actor, int post_id)
{
    int index_actor = isRegistered(actor);
    if (index_actor >= 0)
    {
        int index_post = getPost(post_id); 
        if (index_post >= 0) //if a registered post
        {
            char *username_post = m_posts[index_post]->getPostUser();   
            int index_post_user = isRegistered(username_post);
            m_users[index_actor]->removePost(m_users[index_post_user], post_id);
            return;
        }
        else
        {
            cout << "No post with this id found!" << endl;
            return;
        }
    }
    else
    {
        cout << "User is not registered" << endl;
        return;
    }
}

void System::view_post(char *actor, int post_ID_input)
{
    int index_actor = isRegistered(actor);
    if (index_actor >= 0)
    {
        int post_index = getPost(post_ID_input);
        if (post_index >= 0)
        {
            int post_id = m_posts[post_index]->getPostID();
            char *id_char = intToChar(post_id);
            char *username = m_posts[post_index]->getPostUser();
            char *filename_post = concatanate(username, "_post");
            char *filename = concatanate(filename_post, id_char);
            char *filename_html = concatanate(filename, ".html");
            m_posts[post_index]->saveToHTML(filename_html); //?
            return;
        }
        else
        {
            cout << "No post with this id found!" << endl;
            return;
        }
        return;
    }
    else
    {
        cout << "User is not registered" << endl;
        return;
    }
}

void System::view_all_posts(char *actor, char *subject)
{
    int index_actor = isRegistered(actor);
    int index_subject = isRegistered(subject);
    if ((index_actor >= 0) && (index_subject >= 0))
    {
        const char *username = m_users[index_subject]->getName();
        char *filename = concatanate(username, "_all_posts.html");
        m_users[index_subject]->saveAllPostsToHTML(filename);
        return;
    }
    else
    {
        cout << "User is not registered" << endl;
        return;
    }
}

void System::rename(char *actor, char *subject)
{
    int index_actor = isRegistered(actor);
    if (index_actor >= 0)
    {
        m_users[index_actor]->rename(subject);
        return;
    }
    else
    {
        cout << "User is not registered" << endl;
        return;
    }
}

void System::help()
{
    cout << "Supported methods for FMIBOOK are:\n"
         << "<admin name> add <type of user> <name user/moderator> <age> adds new user with given details\n"
         << "<admin name> remove_user <name user/moderator>              removes a user/moderator\n"
         << "<user/admin/moderator name> post image <filepath to image>  makes an image post\n"
         << "<user/admin/moderator name> post url <url> <description>    makes a url post\n"
         << "<user/admin/moderator name> post text <text>                makes a text post\n"
         << "<admin/moderator name> block <user/moderator name>          blocks user/moderator\n"
         << "<admin/moderator name> unblock <user/moderator name>        unblocks user/moderator\n"
         << "<admin/user/moderator name> remove_post <id_post>           removes post with given id\n"
         << "<admin/user/moderator name> view_post <id_post>             generates an HTML file in the current directory of system\n"
         << "admin/user/moderator name> view_all_posts <username>        generates an HTML file in current directory with all <username> posts\n"
         << "<user> rename <new username>                                user renames itself\n"
         << "info                                                        provides statistics about the program\n"
         << "help                                                        prints this information\n"
         << "quit                                                        ends program" << endl;
}

void System::info() const
{
    int size = m_users.getSize();
    cout << "There are " << size << " users:" << endl;
    //==prints users, their type and their posts
    for (int i = 0; i < size; i++)
    {
        cout << m_users[i]->getName() << " - " << m_users[i]->getTypeOfUser() << ", "
             << m_users[i]->getNumPosts() << " posts." << endl;
    }
    //===prints blocked users===
    cout << "Blocked users are: ";
    int ctr = 0;
    for (int i = 0; i < size; i++)
    {
        if (m_users[i]->getBlolckedStatus())
        {
            cout << m_users[i]->getName() << endl;
            ctr++;
        }
    }
    if (ctr == 0)
        cout << "no blocked users" << endl;

    //===prints oldest and youngest user===
    int max_age = 0;
    int min_age = 99;
    int max_age_index = 0;
    int min_age_index = 0;
    for (int i = 0; i < size; i++)
    {
        int age_current = m_users[i]->getAge();
        if (age_current > max_age)
        {
            max_age = age_current;
            max_age_index = i;
            continue;
        }
        if (age_current < min_age)
        {
            min_age = age_current;
            min_age_index = i;
            continue;
        }
        else
        {
            ;
        }
    }
    cout << "Oldest user is " << m_users[max_age_index]->getName() << " with age " << m_users[max_age_index]->getAge() << " ." << endl;
    cout << "Youngest user is " << m_users[min_age_index]->getName() << " with age " << m_users[min_age_index]->getAge() << " ." << endl;
    
    //===prints user with the most posts===
    int max_posts = 0;
    int max_posts_index = 0;
    for (int i = 0; i < size; i++)
    {
        int posts_current = m_users[i]->getNumPosts();
        if (posts_current > max_posts)
        {
            max_posts = posts_current;
            max_posts_index = i;
            continue;
        }
    }
    cout << "User with the most posts is " << m_users[max_posts_index]->getName() << " with " << m_users[max_posts_index]->getNumPosts() << " posts." << endl;

}

//====run===
void System::run()
{
    cout << "Welcome to FMIBOOK. " << endl;
    //===Chooses admin name and age===
    char *admin_name = new char[MAX_USERNAME_SIZE];
    cout << "Please enter name of Admin and his age:" << endl;
    cin >> admin_name;
    int age_admin;
    cin >> age_admin;
    User *admin = new Admin(admin_name, age_admin);
    m_users.addElement(admin);
    cout << "Admin succesfully chosen.\n"
            "Please enter command:"
         << endl;

    //===Every command will be of type <actor> <action> <subject> [parameter]===
    char *actor = new char[MAX_COMMAND_SIZE];
    char *action = new char[MAX_USERNAME_SIZE];
    char *subject = new char[MAX_USERNAME_SIZE];

    while (true)
    {
        cin >> actor;
        if (strcmp(actor, "info") == 0)
        {
            info();
            continue;
        }
        if (strcmp(actor, "help") == 0)
        {
            help();
            continue;
        }
        if (strcmp(actor, "quit") == 0)
        {
           cout<<"Thank you for using FMIBOOK. "<<endl;
           break;
        }
        cin >> action;
        //===ADD===
        if (strcmp(action, "add") == 0)
        {
            char *type_to_add = new char[50];
            int age;
            cin >> type_to_add;
            cin >> subject;
            cin >> age;
            addUser(actor, type_to_add, subject, age);
            delete[] type_to_add;
            continue;
        }
        //===REMOVE_USER===
        if (strcmp(action, "remove_user") == 0)
        {
            cin >> subject;
            remove_user(actor, subject);
            continue;
        }
        //===BLOCK===
        if (strcmp(action, "block") == 0)
        {
            cin >> subject;
            block(actor, subject);
            continue;
        }
        //===UNBLOCK===
        if (strcmp(action, "unblock") == 0)
        {
            cin >> subject;
            unblock(actor, subject);
            continue;
        }
        //===POST===
        if (strcmp(action, "post") == 0)
        {
            char *type = new char[7];
            cin >> type;
            post(actor, type);
            delete[] type;
            continue;
        }
        //===REMOVE_POST===
        if (strcmp(action, "remove_post") == 0)
        {
            int post_id;
            cin >> post_id;
            remove_post(actor, post_id);
            continue;
        }
        //===VIEW_POST===
        if (strcmp(action, "view_post") == 0)
        {
            int post_ID_input;
            cin >> post_ID_input;
            view_post(actor, post_ID_input);
            continue;
        }
        //===VIEW_ALL_POSTS===
        if (strcmp(action, "view_all_posts") == 0)
        {
            cin >> subject;
            view_all_posts(actor, subject);
            continue;
        }
        //===RENAME===
        if (strcmp(action, "rename") == 0)
        {
            cin >> subject;
            rename(actor, subject);
            continue;
        }
        //===unkown command===
        else
        {
            cout << "Unkown command! Try help for more information." << endl;
            continue;
        }
    } 

    delete[] actor;
    delete[] action;
    delete[] subject;
}
