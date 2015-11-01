#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include <gpgme.h>
int sender(const char* host, int port, const char* msg, int length);
int check_serverstatus(const char* host, int port);
int server();
void init_gpgme (gpgme_protocol_t proto);
void main_encrypter(std::vector<std::string> recipients, std::string msg);
void retrieve();
int start_mainwindow();
void set_user(std::string email);
void set_serverip(std::string ip_addr);
int exit_program();
int msg_to_gpgme_data(std::string enc_msg);
int decrypter(gpgme_data_t in);
void message_reader();
void thread_message_reader(std::vector<std::string> enc_messages, int begin, int end);
void config_edit(std::string key_new, std::string value_new);
void gen_key (const char * xml_string);
void qrecord(std::string key_new, std::string value_new);
void qconvo(std::string convolog, int itr);
int gpg_wait ();
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
std::vector<friends> list_friends(bool secret);
extern std::string user_email;
extern std::string server_ip;
extern int port_value;
extern int debug;
extern int msg_index;
extern bool configfileexist;
#endif
