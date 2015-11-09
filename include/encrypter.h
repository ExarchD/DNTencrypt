#ifndef ENCRYPTER_HPP
#define ENCRYPTER_HPP
 
 
#include <iostream>
#include <string>
#include <vector>
#include <gpgme.h>
#include <objects.h>
 

class Encrypter
{
public:
    Encrypter();
 
private:
bool comparefriends(friends a, friends b);
void load_key ();
void gen_key (const char* xml_string);
int gpg_wait ();
std::string print_data (gpgme_data_t out);
int file_to_gpgme_data(std::string enc_msg);
};
 
struct message_type {
    std::string members;
    std::string message;
};
 
int msg_to_gpgme_data(std::string enc_msg);
void init_gpgme (gpgme_protocol_t proto);
std::vector<friends> list_friends (bool secret);
int decrypter(gpgme_data_t in);
void send_data (std::string formated_message);
message_type encrypter(std::vector<std::string> recipients, std::string msg);
 
#endif /* ENCRYPTER_HPP */
