#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include <gpgme.h>
int sender(const char* host, int port, const char* msg, int length);
int server();
void list_friends();
void init_gpgme (gpgme_protocol_t proto);
std::vector<std::string> names;
std::vector<std::string> emails;
#endif
