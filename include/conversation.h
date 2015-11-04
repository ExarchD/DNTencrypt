#ifndef CONVERSATION_HPP
#define CONVERSATION_HPP

#include <string>
#include <vector>

 
    class Conversation
    {
        public:
            Conversation();
            void load ();
            int send (std::vector<std::string> recipients, std::string msg);
            int retrieve ( std::vector<std::string> recipients);
            int add (std::vector<std::string> recipients, std::string salt);
            int remove (std::vector<std::string> recipients, std::string salt);

        private:
            std::vector<std::string> salts;
            std::vector<std::string> ids;
            std::vector<int> iterators; 
    };

#endif /* CONVERSATION_HPP */
