#ifndef CONVERSATION_HPP
#define CONVERSATION_HPP

#include <string>
#include <vector>
#include <thread>


class Conversation
{

    public:
    Conversation();
    bool running;
    void init ();
    void startretrieval_thread ();
    void endretrieval_thread ();
    int add (std::vector<std::string> recipients, std::string salt, std::string name);
    int remove (std::vector<std::string> recipients, std::string salt);
    int send (std::vector<std::string> recipients, std::string msg);

    private:
    struct conversation_list {
    std::string hash;
    int urgency;
    int iterator;
    int noresponse;
    std::string salt;
};
    std::vector<conversation_list> myconvos;
    std::thread t1;
    int retrieve_thread ();
    std::vector<std::string> salts;
    std::vector<std::string> ids;
    std::vector<int> iterators; 
};

#endif /* CONVERSATION_HPP */
