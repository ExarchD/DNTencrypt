#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include <gpgme.h>
int server();
void main_encrypter(std::vector<std::string> recipients, std::string msg);
void retrieve();
int start_mainwindow();
void set_user(std::string email);
void set_serverip(std::string ip_addr);
int exit_program();
void message_reader();
void thread_message_reader(std::vector<std::string> enc_messages, int begin, int end);
void config_edit(std::string key_new, std::string value_new);
void gen_key (const char * xml_string);
void qrecord(std::string key_new, std::string value_new);
void load_config();
void qconvo(std::string convolog, int itr);
void load_key();
int database_insert(std::string message);
struct message_type {
    std::string pre_hash;
    std::string message;
    std::string recipients;
};
struct convo {
    std::string hash;
    int iterator;
};
message_type encrypter(std::vector<std::string> recipients, std::string msg);
struct friends {
    std::string name;
    std::string email;
};
void save_convos( std::vector<convo> savelist);
std::vector<friends> list_friends(bool secret);
std::vector <convo> load_convos ();
extern std::string user_email;
extern std::string server_ip;
extern int port_value;
extern int debug;
extern int msg_index;
extern bool configfileexist;
#endif
