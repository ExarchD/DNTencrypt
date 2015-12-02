#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include <gpgme.h>
#include <thread>
/** 
 * \mainpage DNTEncrypt documentation
 * 
 * \section intro_sec Introduction
 * The goal of this project is to provide a means of communicating using encrypted messages.
 * This project utilizes <a href="https://www.gnupg.org/(es)/related_software/gpgme/index.html">GPGME</a>
 * to provide encryption, partially to encourage GPG keys in email signatures and other uses. Messages are 
 * sent entirely encrypted to a server, and hashes are used to retrieve these messages. The server is extremely 
 * simple and does no more processing than entering and retrieving messages and hashes from an sql database.
 * 
 * \section Methods
 * \subsection Encryption
 * Encryption uses gpg keys that are available in the system keyring. The user is trusted to initially retrieve
 * and sign these keys. Unsigned keys will give a warning to show if some conversation members are not yet trusted.
 *
 * \subsection Hashes
 * Hashes are created using a salt generated for each conversation, an iterator counting the number of messages(for uniqueness),
 * and the desired information. For example, when querying the server if there are new messages, a client creates a hash from the salt, involved members,
 * and the conversation iterator value. Then if a message is returned, the iterator is incremented and the client makes a new query. If no message is
 * returned, the client will wait longer to query again.
 */
int server();
void main_encrypter(std::vector<std::string> recipients, std::string msg);
int exit_program();
void thread_message_reader(std::vector<std::string> enc_messages, int begin, int end);
void config_edit(std::string key_new, std::string value_new);
void gen_key (const char * xml_string);
void load_key();
int database_insert(std::string message);
struct convo {
    std::string hash;
    int iterator;
};
struct friends {
    std::string name;
    std::string email;
};
struct enc_convo{
    int urgency;
    int noresponse;
    int iterator;
    std::string enc_info;
};
void record_convos(std::vector <enc_convo> allenc_convos);
std::vector <enc_convo> load_convos();
std::vector<friends> list_friends(bool secret);
extern std::string user_email;
extern std::string server_ip;
extern int port_value;
extern int debug;
extern int msg_index;
extern bool configfileexist;
#endif
