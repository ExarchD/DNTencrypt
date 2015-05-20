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
#include "t-support.h"
#include <vector>
#include <iostream>
using namespace std;


void
print_data (gpgme_data_t dh)
{
#define BUF_SIZE 512
  int length;
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
    const char * msg = b.c_str();
   // cout << b << endl;
    sender("127.0.0.1", 55566, msg, 512);
    msg=NULL;
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


std::vector<friends> list_friends () {
std::vector<friends> friendlist;

  gpgme_check_version (NULL);
  gpgme_data_t in, out;
  gpgme_encrypt_result_t result;


gpgme_ctx_t ctx;
gpgme_key_t key;
gpgme_error_t err = gpgme_new (&ctx);
  init_gpgme (GPGME_PROTOCOL_OpenPGP);

  fail_if_err (err);

    if (!err)
       {
         err = gpgme_op_keylist_start (ctx, "", 0);
         while (!err)
           {
             err = gpgme_op_keylist_next (ctx, &key);
             if (err)
               break;
             if (key->uids && key->uids->name) {
             if (key->uids && key->uids->email){
		friends afriend ={key->uids->name,  key->uids->email};
   		friendlist.push_back(afriend);
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
     return friendlist;
}








int main (int argc, char* argv[] ) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


return 0;
}
