#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include <gpgme.h>
#include <thread>
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
