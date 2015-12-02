#ifndef CONVERSATION_HPP
#define CONVERSATION_HPP

#include <string>
#include <vector>
#include <thread>
#include <encrypter.h>


class Conversation
{

    public:
        /** 
         * @brief A simplier conversation struct for gui purposes
         */
    struct gui_convo {
        /** 
         * @brief A combination of the salt, a delimiter, and the user-friendly name 
         * of the conversation.
         */
    std::string name;
    /** 
     * @brief A vector of the recipients in the form of emails (maybe should change this to be 
     * recipient objects)
     */
    std::vector<std::string> recipients;
};
    Conversation();
    /** 
     * @brief A indicator about the retrieval thread status
     */
    bool running;
    /** 
     * @brief Initializes the Conversation object
     */
    void init ();
    std::vector<gui_convo> list ();
    /** 
     * @brief Starts the retrieval thread
     */
    void startretrieval_thread ();
    /** 
     * @brief Ends the retrieval thread
     */
    void endretrieval_thread ();
    /** 
     * @brief Runs through the list of conversations and produces a
     * simpler conversation object
     * 
     * @return Returns the gui_convo objects for the gui to use 
     */
    std::vector<gui_convo> list_convos ();
    /** 
     * @brief Adds a new conversation to the vector of convos
     * 
     * @param recipients List of intended recipients
     * @param salt Salt for disquising hashes
     * @param name A user identifiable name for the conversation, has no internal purpose
     * 
     * @return Status code on success
     */
    int add (std::vector<std::string> recipients, std::string salt, std::string name);
    int remove (std::vector<std::string> recipients, std::string salt);
    /** 
     * @brief Encrypts message and then sends it to server
     * 
     * @param recipients List of recipients
     * @param msg Unencrypted message
     * 
     * @return Status code on success
     */
    int send (std::vector<std::string> recipients, std::string msg);
    void csave_convos();
    void cload_convos();

    /** 
     * @brief A conversation struct, with all the necessary information about an individual conversation
     */
struct conversationItem {
    /** 
     * @brief Decides how frequently to query the server for new messages
     */
    int urgency;
    /** 
     * @brief How much time has passed since a retrieval
     */
    int noresponse;
    /** 
     * @brief Number of messages, used for hashing purposes
     */
    int iterator;
    /** 
     * @brief Salt to disquise the hash
     */
    std::string salt;
    /** 
     * @brief A list of intended recipients
     */
    std::vector<std::string> recipients;
};
    std::vector<conversationItem> myconvos;
    std::vector<conversationItem> myconvos_intime;
    private:
    std::thread t1;
    int retrieve_thread ();
    std::vector<std::string> salts;
    std::vector<std::string> ids;
    /** 
     * @brief Vector of conversation iterators
     */
    std::vector<int> iterators; 
};
    

#endif /* CONVERSATION_HPP */
