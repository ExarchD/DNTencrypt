#include "objects.h"
#include <gpgme.h>
#include "t-support.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "sha1.h"
using namespace std;

	gpgme_key_t key_sign;


void print_data (gpgme_data_t dh)
{
#define BUF_SIZE 512
	//      int length;
	char buf[BUF_SIZE + 1];
	int ret;
	string b;
	ret = gpgme_data_seek (dh, 0, SEEK_SET);
	if (ret)
		fail_if_err (gpgme_err_code_from_errno (errno));
	while ((ret = gpgme_data_read (dh, buf, BUF_SIZE)) > 0){
		for (int x = 0; x < ret; x++) {
			b+= buf[x];
		}
		//  fwrite (buf, ret, 1, stdout);
		}
	string c = "HI";
	      const char * msg = c.c_str();
	// cout << b << endl;
	 //     sender("127.0.0.1", 55566, msg, 512);
//          sender(server_ip.c_str(), 66655, msg, 512);
	//      msg=NULL;
	//    client("128.141.249.147", 55566, msg, 512);
	cout << b << endl;

	if (ret < 0)
		fail_if_err (gpgme_err_code_from_errno (errno));
}


void init_gpgme (gpgme_protocol_t proto)
{
	gpgme_error_t err;

	gpgme_check_version (NULL);
	setlocale (LC_ALL, "");
	gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifndef HAVE_W32_SYSTEM
//	gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif

	err = gpgme_engine_check_version (proto);
	fail_if_err (err);
	gpgme_ctx_t ctx;
	err = gpgme_get_key (ctx, user_email.c_str(),&key_sign, 0);
}

	gpgme_error_t
passphrase_cb (void *opaque, const char *uid_hint, const char *passphrase_info,
		int last_was_bad, int fd)
{
	//write (fd, "abc\n", 4);
	write (fd, "1234\n", 5);	
	return 0;
}


bool comparefriends(friends a, friends b) {
	return a.name.compare(b.name) < 0;
}

vector<friends> list_friends (bool secret) {
	vector<friends> friendlist;
	vector<string> rejected;
	string line;
	ifstream myfile;
	myfile.open("rejected.txt");
	while (getline (myfile, line)) rejected.push_back(line);
	myfile.close();
	gpgme_check_version (NULL);
	//      gpgme_encrypt_result_t result;
	gpgme_ctx_t ctx;
	gpgme_key_t key;
	gpgme_error_t err = gpgme_new (&ctx);
	int skip = 0;
	fail_if_err (err);
	if (!err)
	{
		err = gpgme_op_keylist_start (ctx, "", secret);
		while (!err)
		{
			err = gpgme_op_keylist_next (ctx, &key);
			if (err)
				break;
			if (key->uids && key->uids->name) {
				if (key->uids && key->uids->email){
					skip = 0;
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


int decrypter(string enc_msg, bool record) {
  gpgme_ctx_t ctx;
  gpgme_error_t err;
  gpgme_data_t in, out;
  gpgme_decrypt_result_t result;
  err = gpgme_new (&ctx);
  fail_if_err (err);
  if (err) return 1;
  gpgme_key_t key;
  const char *buf = enc_msg.c_str();
  size_t nread=strlen(buf);
  err = gpgme_data_new_from_mem (&in, buf, nread, 1 );
  fail_if_err (err);
  if (err) return 1;

  err = gpgme_data_new (&out);
  fail_if_err (err);
  if (err) return 1;

  err = gpgme_op_decrypt_verify (ctx, in, out);
  fail_if_err (err);
  if (err) return 1;
  result = gpgme_op_decrypt_result (ctx);

  if (result->unsupported_algorithm)
    {
      fprintf (stderr, "%s:%i: unsupported algorithm: %s\n",
               __FILE__, __LINE__, result->unsupported_algorithm);
      return (1);
    }

  print_data (out);

  gpgme_data_release (in);
  gpgme_data_release (out);
  gpgme_release (ctx);
  return 0;

}	


int decrypter2(string enc_msg2, bool record2) {
  gpgme_ctx_t ctx2;
  gpgme_error_t err2;
  gpgme_data_t in2, out2;
  gpgme_decrypt_result_t result2;
  err2 = gpgme_new (&ctx2);
  fail_if_err (err2);
  if (err2) return 1;
  const char *buf2 = enc_msg2.c_str();
  size_t nread2=strlen(buf2);
  err2 = gpgme_data_new_from_mem (&in2, buf2, nread2, 1 );
  fail_if_err (err2);
  if (err2) return 1;

  err2 = gpgme_data_new (&out2);
  fail_if_err (err2);
  if (err2) return 1;

  err2 = gpgme_op_decrypt_verify (ctx2, in2, out2);
  fail_if_err (err2);
  if (err2) return 1;
  result2 = gpgme_op_decrypt_result (ctx2);

  if (result2->unsupported_algorithm)
    {
      fprintf (stderr, "%s:%i: unsupported algorithm: %s\n",
               __FILE__, __LINE__, result2->unsupported_algorithm);
      return (1);
    }

  print_data (out2);

  gpgme_data_release (in2);
  gpgme_data_release (out2);
  gpgme_release (ctx2);
  return 0;

}
void send_data (string formated_message)
{
#define BUF_SIZE 512
        //      int length;
        char buf[BUF_SIZE + 1];
        int ret;
              const char * msg = formated_message.c_str();
              sender(server_ip.c_str(), 6655, msg, 512);
//              sender("90.41.180.202", 66655, msg, 512);
        //      msg=NULL;
        //    client("128.141.249.147", 55566, msg, 512);
        cout << formated_message << endl;

        if (ret < 0)
                fail_if_err (gpgme_err_code_from_errno (errno));
}


void encrypter(vector<string> recipients, string msg) {
	gpgme_check_version (NULL);
	gpgme_ctx_t ctx;
	gpgme_error_t err;
	gpgme_data_t in, out;
	gpgme_encrypt_result_t result;
	err = gpgme_new (&ctx);
	fail_if_err (err);
	gpgme_set_armor (ctx, 1);
	recipients.push_back(user_email);
	int n_recipients = recipients.size();
	gpgme_key_t key[n_recipients];
	string message_key;
	for (int n = 0; n < n_recipients; n++) {key[n+1]=NULL;}
	for (int n = 0; n < n_recipients; n++) {
        if (recipients[n] != user_email){
            message_key+=sha1(recipients[n]);
            if (n!=n_recipients-2) message_key+=",";
        }
		err = gpgme_get_key (ctx, recipients[n].c_str(),
				&key[n], 0);
		fail_if_err (err);
	}
	err = gpgme_data_new_from_mem (&in, msg.c_str(), msg.length(), 0);
	fail_if_err (err);
	err = gpgme_data_new (&out);
	fail_if_err (err);
	gpgme_signers_clear(ctx);
	gpgme_key_t key_sign;
	err = gpgme_get_key (ctx, user_email.c_str(),&key_sign, 0);
	fail_if_err (err);
	err = gpgme_signers_add(ctx,key_sign);
	fail_if_err (err);
	err = gpgme_op_encrypt_sign (ctx, key, GPGME_ENCRYPT_ALWAYS_TRUST, in, out);
	fail_if_err (err);
	result = gpgme_op_encrypt_result (ctx);
	if (result->invalid_recipients)
	{
		fprintf (stderr, "Invalid recipient encountered: %s\n",
				result->invalid_recipients->fpr);
		exit (1);
	}
#define BUF_SIZE 512
	//        int length;
	char buf[BUF_SIZE + 1];
	int ret;

	string b;
	ret = gpgme_data_seek (out, 0, SEEK_SET);
	if (ret)
		fail_if_err (gpgme_err_code_from_errno (errno));
	while ((ret = gpgme_data_read (out, buf, BUF_SIZE)) > 0){
		for (int x = 0; x < ret; x++) {
			b+= buf[x];
		}
	}
        send_data(sha1(b)+";"+b+";"+message_key);
     //   send_data("HI");
	//	print_data(out);
	gpgme_data_release (in);
	gpgme_data_release (out);
	gpgme_release (ctx);

}

