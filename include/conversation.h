#ifndef CONVERSATION_HPP
#define CONVERSATION_HPP

#include <string>
#include <vector>
#include <thread>


class Conversation
{

    public:
    struct gui_convo {
    std::string name;
    std::vector<std::string> recipients;
};
    Conversation();
    bool running;
    void init ();
    std::vector<gui_convo> list ();
    void startretrieval_thread ();
    void endretrieval_thread ();
    std::vector<gui_convo> list_convos ();
    int add (std::vector<std::string> recipients, std::string salt, std::string name);
    int remove (std::vector<std::string> recipients, std::string salt);
    int send (std::vector<std::string> recipients, std::string msg);

    private:
struct conversationItem {
    /* std::string title; */
    int urgency;
    int noresponse;
    int iterator;
    std::string salt;
    std::vector<std::string> recipients;
};
    std::vector<conversationItem> myconvos;
    std::vector<conversationItem> myconvos_intime;
    std::thread t1;
    int retrieve_thread ();
    std::vector<std::string> salts;
    std::vector<std::string> ids;
    std::vector<int> iterators; 
};
    

#endif /* CONVERSATION_HPP */
