#ifndef ENCRYPTER_HPP
#define ENCRYPTER_HPP


#include <iostream>
#include <string>
#include <vector>
#include <gpgme.h>
#include <objects.h>

/* Encrypter(); */
/* ~Encrypter(); */

bool comparefriends(friends a, friends b);
/** 
 * @brief Loads the user's primary key
 */
void load_key ();
struct message_type {
    std::string members;
    std::string message;
};

void gen_key (const char* xml_string);
int gpg_wait ();
std::string print_data (gpgme_data_t out);
int file_to_gpgme_data(std::string enc_msg);
message_type encrypter(std::vector<std::string> recipients, std::string msg);
std::string decrypter(std::string enc_msg, bool verify);

int msg_to_gpgme_data(std::string enc_msg);

/** 
 * @brief Initializes the gpgme engine
 * 
 * @param proto The protocol for the engine
 */
void init_gpgme (gpgme_protocol_t proto);

/** 
 * @brief Loads all 'friends' by looping through 
 * the gpg keyring.
 * 
 * @param secret specifies whether to look for secret
 * keys, or in other words, local user keys capable of 
 * decrypting
 * 
 * @return A vector of friends objects, which is both the 
 * email and ID
 */
std::vector<friends> list_friends (bool secret);
void send_data (std::string formated_message);
/* userkey */


#endif /* ENCRYPTER_HPP */
