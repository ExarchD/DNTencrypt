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
    void startretrieve (Conversation d);
    void startretrieve2 ();
    void endretrieve ();
    int send (std::vector<std::string> recipients, std::string msg);
    int retrieve ();
    int add (std::vector<std::string> recipients, std::string salt);
    int remove (std::vector<std::string> recipients, std::string salt);
    std::thread t1;

    private:
    std::vector<std::string> salts;
    std::vector<std::string> ids;
    std::vector<int> iterators; 
};

#endif /* CONVERSATION_HPP */
