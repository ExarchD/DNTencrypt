/* #include "objects.h" */
#include <thread>
#include <gpgme.h>
#include "t-support.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "sha1.h"
#include <locale.h>
#include <encrypter.h>
using namespace std;

gpgme_key_t key_sign;
gpgme_ctx_t ctx;


void init_gpgme (gpgme_protocol_t proto)
{
    gpgme_error_t err;

    gpgme_check_version (NULL);
    setlocale (LC_ALL, "");
    gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifndef HAVE_W32_SYSTEM
    //      gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif

    err = gpgme_engine_check_version (proto);
    fail_if_err (err);
}

void load_key () {
    gpgme_error_t err;
    err = gpgme_new (&ctx);
    fail_if_err (err);
    cout << "user email: " << user_email << endl;
    err = gpgme_get_key (ctx, user_email.c_str(),&key_sign, 0);
    /* cout << key_sign->subkeys->keyid << endl; */
    fail_if_err (err);
}

void gen_key (const char* xml_string) 
{
    gpgme_error_t err;
    err = gpgme_op_genkey_start(ctx, xml_string,  NULL, NULL);
    fail_if_err (err);
}

int gpg_wait () {
    gpgme_error_t err;
    gpgme_wait(ctx, &err, 1);
    return 0;
}


bool comparefriends(friends a, friends b) {
    return a.name.compare(b.name) < 0;
}

vector<friends> list_friends (bool secret) {
    if (debug > 0 ) cout << "loading friends" << endl;
    vector<friends> friendlist;
    vector<string> rejected;
    string line;
    ifstream myfile;
    if (debug == 1 ) std::cout << "loading file of rejected keys" << std::endl;
    myfile.open("rejected.txt");
    while (getline (myfile, line)) rejected.push_back(line);
    if (debug == 1 ) std::cout << "loaded rejects to vector" << std::endl;
    myfile.close();
    //	gpgme_check_version (NULL);
    //      gpgme_encrypt_result_t result;
    gpgme_key_t key;
    gpgme_error_t err = gpgme_new (&ctx);
    int skip = 0;
    fail_if_err (err);
    if (debug > 1 ) cout << "looping through list" << endl;
    if (!err)
    {
        err = gpgme_op_keylist_start (ctx, "", secret);
        while (!err)
        {
            err = gpgme_op_keylist_next (ctx, &key);
            if (debug > 1 ) cout << "next key" << endl;
            if (err)
                break;
            if (key->uids && key->uids->name) {
                if (key->uids && key->uids->email){
                    if (debug > 1 ) cout << "key has email and id" << endl;
                    skip = 0;
                    if (  !secret && user_email == key->uids->email ) skip =1;
                    for (unsigned int l=0; l<rejected.size(); l++) {
                        if (!secret && rejected[l] == key->uids->email) skip = 1;
                    }
                    if (!skip) {
                        friends afriend ={key->uids->name,  key->uids->email};
                        friendlist.push_back(afriend);
                    }
                }}
            putchar ('\n');
            gpgme_key_release (key);
        }
        gpgme_release (ctx);
    }
    if (gpg_err_code (err) != GPG_ERR_EOF)
    {
        fprintf (stderr, "can not list keys: %s\n", gpgme_strerror (err));
        exit (1);
    }
    sort(friendlist.begin(), friendlist.end(), comparefriends);
    return friendlist;
}

string print_data (gpgme_data_t out) {
#define BUF_SIZE 512
    //        int length;
    char buf[BUF_SIZE + 1];
    int ret;

    string b;
    if (debug > 1 ) cout << "seeking through data"<< endl;
    ret = gpgme_data_seek (out, 0, SEEK_SET);
    if (debug > 1 ) cout << "loading data into a string" << endl;
    if (ret)
        fail_if_err (gpgme_err_code_from_errno (errno));
    while ((ret = gpgme_data_read (out, buf, BUF_SIZE)) > 0){
        for (int x = 0; x < ret; x++) {
            b+= buf[x];
        }
    }
    return b;
}






string decrypter(string enc_msg, bool sigcheck) {
    gpgme_error_t err;
    gpgme_data_t in, out;
    err = gpgme_new (&ctx);
    fail_if_err (err);
    const char *buf = enc_msg.c_str();
    size_t nread=strlen(buf);
    err = gpgme_data_new_from_mem (&in, buf, nread, 1 );
    fail_if_err (err);

    gpgme_decrypt_result_t result;
    gpgme_verify_result_t sig_result;
    err = gpgme_data_new (&out);
    fail_if_err (err);


    gpgme_key_t key;
    err = gpgme_op_decrypt_verify (ctx, in, out);
    fail_if_err (err);
    sig_result = gpgme_op_verify_result (ctx);
    err = gpgme_get_key ( ctx, sig_result->signatures->fpr,&key, 0); 
    cout << key->uids->name << endl;
    cout << key->uids->email << endl;
    fail_if_err (err);

    if (sigcheck)
    {
        time_t timeGMT = (time_t)sig_result->signatures->timestamp;
        cout << ctime (&timeGMT) << endl;;
        fail_if_err (err);
    }
    result = gpgme_op_decrypt_result (ctx);
    if (sigcheck)
    {
        cout << result->recipients << endl;

        key=NULL;

        err = gpgme_op_keylist_start (ctx, "", 0);
        while (!err)
        {
            err = gpgme_op_keylist_next (ctx, &key);
            if (debug > 1 ) cout << "next key" << endl;
            if (err)
                break;
            if (key->uids && key->uids->name) {
                if (key->uids && key->uids->email){
                    if (debug > 1 ) cout << "key has email and id" << endl;
                    cout << key->uids->email << endl;
                }
            }
        }
    }
    string b;
#define BUF_SIZE 512
    char buf2[BUF_SIZE + 1];
    if (debug > 1 ) cout << "seeking through data"<< endl;
    int ret = gpgme_data_seek (out, 0, SEEK_SET);
    if (debug > 1 ) cout << "loading data into a string" << endl;
    cout << "5" << endl;
    if (ret)
        fail_if_err (gpgme_err_code_from_errno (errno));
    while ((ret = gpgme_data_read (out, buf2, BUF_SIZE)) > 0){
        for (int x = 0; x < ret; x++) {
            b+= buf2[x];
        }
    }
    gpgme_data_release (in);
    gpgme_data_release (out);
    gpgme_release (ctx);
    return b;

}	

/* int msg_to_gpgme_data(string enc_msg) { */
/*     gpgme_error_t err; */
/*     gpgme_data_t in; */
/*     err = gpgme_new (&ctx); */
/*     fail_if_err (err); */
/*     if (err) return 1; */
/*     const char *buf = enc_msg.c_str(); */
/*     size_t nread=strlen(buf); */
/*     err = gpgme_data_new_from_mem (&in, buf, nread, 1 ); */
/*     fail_if_err (err); */
/*     if (err) return 1; */
/*     decrypter(in); */
/*     return 0; */
/* } */

/* int file_to_gpgme_data(string enc_msg) { */
/*     gpgme_error_t err; */
/*     gpgme_data_t in; */
/*     err = gpgme_new (&ctx); */
/*     fail_if_err (err); */
/*     if (err) return 1; */
/*     const char *buf = enc_msg.c_str(); */
/*     size_t nread=strlen(buf); */
/*     err = gpgme_data_new_from_mem (&in, buf, nread, 1 ); */
/*     fail_if_err (err); */
/*     if (err) return 1; */
/*     decrypter(in); */
/*     return 0; */
/* } */





void send_data (string formated_message)
{
    const char * msg = formated_message.c_str();
    if (debug > 3 ) cout << formated_message << endl;
    //        	cout << formated_message << endl;
    /* thread sending (sender,server_ip.c_str(), 6655, msg, 512); */
    /* sending.detach(); */

    /* sender(server_ip.c_str(), port_value, msg, 512); */
}


message_type encrypter(vector<string> recipients, string msg) {
    if (debug > 0 )  cout << "encryption algorythm starting" << endl;
    gpgme_check_version (NULL);
    gpgme_error_t err;
    gpgme_data_t in, out;
    err = gpgme_new (&ctx);


    fail_if_err (err);
    gpgme_set_armor (ctx, 1);
    recipients.push_back(user_email);
    if (debug > 1 ) cout << "recipients loaded"<< endl;
    int n_recipients = recipients.size();
    gpgme_key_t key[n_recipients];
    if (debug > 1 ) cout << "clearing message"<< endl;
    string message_key="";
    string recipts_key="";
    if (debug > 1 ) cout << "cleared message"<< endl;
    string ident;
    for (int n = 0; n < n_recipients; n++) {key[n+1]=NULL;}
    for (int n = 0; n < n_recipients; n++) {
        err = gpgme_get_key (ctx, recipients[n].c_str(),
                &key[n], 0);
        fail_if_err (err);
        message_key+=key[n]->subkeys->keyid;
        if (n!=n_recipients-1) message_key+=",";
        /* if (recipients[n] != user_email){ */
        /*     if (debug > 1 ) cout << "adding hash of sub keys"<< endl; */
        /*     recipts_key+=sha1(key[n]->subkeys->keyid+msg_index); */
        /*     if (debug > 1 ) cout << "adding delimiter"<< endl; */
        /*     if (n!=n_recipients-2) recipts_key+=","; */
        /* } */
    }
    err = gpgme_data_new_from_mem (&in, msg.c_str(), msg.length(), 0);
    if (debug > 1 ) cout << "loading message"<< endl;
    fail_if_err (err);
    err = gpgme_data_new (&out);
    fail_if_err (err);
    if (debug > 1 ) cout << "cleaning signers"<< endl;
    gpgme_signers_clear(ctx);
    if (debug > 1 ) cout << "adding signer key"<< endl;
    err = gpgme_signers_add(ctx,key_sign);
    fail_if_err (err);
    if (debug > 1 ) cout << "processing result"<< endl;
    if (debug > 1 ) cout << "processed result"<< endl;
    err = gpgme_op_encrypt_sign (ctx, key, GPGME_ENCRYPT_ALWAYS_TRUST, in, out);
    if (debug > 1 ) cout << "encrypted and signed message"<< endl;
    fail_if_err (err);
#define BUF_SIZE 512
    //        int length;
    char buf[BUF_SIZE + 1];
    int ret;

    string b;
    if (debug > 1 ) cout << "seeking through data"<< endl;
    ret = gpgme_data_seek (out, 0, SEEK_SET);
    if (debug > 1 ) cout << "loading data into a string" << endl;
    if (ret)
        fail_if_err (gpgme_err_code_from_errno (errno));
    while ((ret = gpgme_data_read (out, buf, BUF_SIZE)) > 0){
        for (int x = 0; x < ret; x++) {
            b+= buf[x];
        }
    }
    message_type tmesg;
    tmesg.members=message_key;
    tmesg.message=b;
    gpgme_data_release (in);
    gpgme_data_release (out);
    gpgme_release (ctx);
    return tmesg;

}

