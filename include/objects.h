#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include <gpgme.h>
int sender(const char* host, int port, const char* msg, int length);
int server();
void init_gpgme (gpgme_protocol_t proto);
void encrypter(std::vector<std::string> recipients, std::string msg);
void retrieve();
int unlock_master_key(std::string pass, std::string email);
int exit_program();
struct friends {
   std::string name;
   std::string email;
};
std::vector<friends> list_friends(bool secret);

#endif
