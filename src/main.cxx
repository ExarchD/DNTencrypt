#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include "objects.h"
#include <QApplication>
#include <gpgme.h>
#include <mainwindow.h>
#include <passphrase.h>
#include "t-support.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

    gpgme_ctx_t ctx_main;
    gpgme_error_t err_main;
    gpgme_key_t key_main = NULL;



void print_data (gpgme_data_t dh)
{
#define BUF_SIZE 512
	//	int length;
	char buf[BUF_SIZE + 1];
	int ret;
	string b;
	ret = gpgme_data_seek (dh, 0, SEEK_SET);
	if (ret)
		fail_if_err (gpgme_err_code_from_errno (errno));
	cout << "HI"<< endl;
	while ((ret = gpgme_data_read (dh, buf, BUF_SIZE)) > 0){
		for (int x = 0; x < ret; x++) {
			cout << "in loop"<< endl;
			b+= buf[x];
		}
		//  fwrite (buf, ret, 1, stdout);
	}
	//	const char * msg = b.c_str();
	// cout << b << endl;
	//	sender("127.0.0.1", 55566, msg, 512);
	//	msg=NULL;
	//    client("128.141.249.147", 55566, msg, 512);
	// cout << b << endl;

	if (ret < 0)
		fail_if_err (gpgme_err_code_from_errno (errno));
}


	void
init_gpgme (gpgme_protocol_t proto)
{
	gpgme_error_t err;

	gpgme_check_version (NULL);
	setlocale (LC_ALL, "");
	gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifndef HAVE_W32_SYSTEM
	gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif

	err = gpgme_engine_check_version (proto);
	fail_if_err (err);
}

bool comparefriends(friends a, friends b) {
	return a.name.compare(b.name) < 0;
}

int  unlock_master_key(string pass, string email) {
        gpgme_passphrase_cb_t phrase;
        err_main = gpgme_get_key (ctx_main, email.c_str(), &key_main, 1);
return 1;
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
	//	gpgme_encrypt_result_t result;
	gpgme_ctx_t ctx;
	gpgme_key_t key;
	gpgme_error_t err = gpgme_new (&ctx);
	//init_gpgme (GPGME_PROTOCOL_OpenPGP);
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
						if (rejected[l] == key->uids->email) skip = 1;
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


//string decrypter(




void encrypter(vector<string> recipients, string msg) {


	//sort(recipients.begin(), recipients.end());
	gpgme_check_version (NULL);
	gpgme_ctx_t ctx;
	gpgme_error_t err;
	gpgme_data_t in, out;
	gpgme_encrypt_result_t result;
	//init_gpgme (GPGME_PROTOCOL_OpenPGP);
	err = gpgme_new (&ctx);
	fail_if_err (err);
	gpgme_set_armor (ctx, 1);
	int n_recipients = recipients.size();
	cout << n_recipients << endl;
	gpgme_key_t key[n_recipients];
	for (int n = 0; n < n_recipients; n++) {key[n+1]=NULL;}
	for (int n = 0; n < n_recipients; n++) {
		cout << recipients[n].c_str() << endl;
		err = gpgme_get_key (ctx, recipients[n].c_str(),
				&key[n], 0);
		fail_if_err (err);
	}
	err = gpgme_data_new_from_mem (&in, msg.c_str(), msg.length(), 0);
	fail_if_err (err);
	err = gpgme_data_new (&out);
	fail_if_err (err);

	err = gpgme_op_encrypt (ctx, key, GPGME_ENCRYPT_ALWAYS_TRUST, in, out);
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
	cout << b << endl;
	//	print_data(out);
	gpgme_data_release (in);
	gpgme_data_release (out);
	gpgme_release (ctx);

}

int exit_program() {
	exit(0);
}

void retrieve() {
	while (1) {
		std::cout << "waiting 2 seconds" << std::endl;
		sleep(2);
	}
}

int main (int argc, char* argv[] ) {

	init_gpgme (GPGME_PROTOCOL_OpenPGP);
	QApplication a(argc, argv);
	//    MainWindow w;
	Passphrase w;
	w.show();
	return a.exec();
	//
	//	string msg="HI";
	//	vector<string> email_list;
	//	email_list.push_back("pluthd@macworkie.com");
	//	email_list.push_back("pluthd@gmail.com");
	//        encrypter(email_list, msg);

	return 0;
}
