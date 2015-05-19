#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include "t-support.h"
#include <string.h>
#include <gpgme.h>
#include <iostream>
#include <objects.h>
using namespace std;



void list_friends () {

  gpgme_check_version (NULL);
  gpgme_data_t in, out;
  gpgme_encrypt_result_t result;

names.clear();
emails.clear();

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
//             printf ("%s:", key->subkeys->keyid);
             if (key->uids && key->uids->name)
                 names.push_back(key->uids->name);
//             printf (" %s", key->uids->name);d
             if (key->uids && key->uids->email)
                 emails.push_back(key->uids->email);
//               printf (" <%s>", key->uids->email);
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

}
