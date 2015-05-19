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


int main (int argc, char* argv[] ) {

//    QApplication a(argc, argv);
//    MainWindow w;
 //   w.show();

//    return a.exec();

  gpgme_check_version (NULL);
  gpgme_ctx_t ctx;
  gpgme_error_t err;
  gpgme_data_t in, out;
 // gpgme_key_t key = {  NULL };
  gpgme_key_t key[3] = { NULL, NULL, NULL };
  gpgme_encrypt_result_t result;

  init_gpgme (GPGME_PROTOCOL_OpenPGP);

  err = gpgme_new (&ctx);
  fail_if_err (err);
  gpgme_set_armor (ctx, 1);


  string x = "no";

  err = gpgme_get_key (ctx, "pluthd@macworkie.com",
		       &key[0], 0);
  fail_if_err (err);
//  err = gpgme_get_key (ctx, "asdfg@gmail.com",
//		       &key[1], 0);
//  fail_if_err (err);



 while ( x != "") {
    std::string buffer;
    std::getline(std::cin, buffer);
   x = buffer.c_str();
   if (x == "exit_program") break;

   if (x == "recipient") {
  std::cout << "Please enter recipient id" << std::endl;
    std::getline(std::cin, buffer);
  err = gpgme_get_key (ctx, buffer.c_str(),
		       &key[1], 0);
  fail_if_err (err);
  std::cout << "Recipient changed to " << buffer.c_str() << std::endl;
  continue;
} 
  err = gpgme_data_new_from_mem (&in, buffer.c_str(), buffer.length(), 0);
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

//  x=buffer.c_str();
  print_data (out);
}

  list_friends ();
// write for loop to release all held keys
//  gpgme_key_unref (key[0]);
//  gpgme_key_unref (key[1]);
  gpgme_data_release (in);
  gpgme_data_release (out);
  gpgme_release (ctx);

return 0;
}
