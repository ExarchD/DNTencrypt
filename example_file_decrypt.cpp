#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <locale.h>
#include <gpgme.h>
#include <cstring>
#include <stdio.h> 
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
#ifndef DIM
#define DIM(v)		     (sizeof(v)/sizeof((v)[0]))
#endif

#define fail_if_err(err)					\
  do								\
    {								\
      if (err)							\
        {							\
          fprintf (stderr, "%s:%d: %s: %s\n",			\
                   __FILE__, __LINE__, gpgme_strsource (err),	\
		   gpgme_strerror (err));			\
          						\
        }							\
    }								\
  while (0)

void
write_data (gpgme_data_t dh)
{
#define BUF_SIZE 512
  char buf[BUF_SIZE + 1];
  int ret;
  FILE *fp;
  
  if ((fp=fopen("decrypted.file", "w+")) == 0) {
	  
	  printf("File creation error\n");
	  
  }
	
  ret = gpgme_data_seek (dh, 0, SEEK_SET);
  if (ret)
    fail_if_err (gpgme_err_code_from_errno (errno));
  while ((ret = gpgme_data_read (dh, buf, BUF_SIZE)) > 0)
    fwrite (buf, ret, 1, fp);
  if (ret < 0)
    fail_if_err (gpgme_err_code_from_errno (errno));
}


void
print_data (gpgme_data_t dh)
{
#define BUF_SIZE 512
  char buf[BUF_SIZE + 1];
  int ret;
  
  ret = gpgme_data_seek (dh, 0, SEEK_SET);
  if (ret)
    fail_if_err (gpgme_err_code_from_errno (errno));
  while ((ret = gpgme_data_read (dh, buf, BUF_SIZE)) > 0)
    fwrite (buf, ret, 1, stdout);
  if (ret < 0)
    fail_if_err (gpgme_err_code_from_errno (errno));
}


// the password fo the key should be written here
gpgme_error_t
passphrase_cb (void *opaque, const char *uid_hint, const char *passphrase_info,
	       int last_was_bad, int fd)
{
  //write (fd, "abc\n", 4);
  write (fd, "1234\n", 5);	
  return 0;
}


char *
make_filename (const char *fname)
{
  const char *srcdir = getenv ("srcdir");
  char *buf;

  if (!srcdir)
    srcdir = ".";
  buf = (char*)malloc (strlen(srcdir) + strlen(fname) + 2);
  if (!buf) 
    exit (8);
  strcpy (buf, srcdir);
  strcat (buf, "/");
  strcat (buf, fname);
  return buf;
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


int decrypt_file()
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;
  gpgme_data_t in, out;
  gpgme_decrypt_result_t result;
	// write the encrypted filename here, vmlinux-copiled.gpg will be used

  init_gpgme (GPGME_PROTOCOL_OpenPGP);

  err = gpgme_new (&ctx);
  fail_if_err (err);
  if (err) return 1;
 

  gpgme_key_t key;

                err = gpgme_get_key (ctx, "pluthd@gmail.com", &key, 0);

  gpgme_set_passphrase_cb (ctx, passphrase_cb, NULL);
        std::string line;
        ifstream encryp_file;
        encryp_file.open("messages.txt");
        string s;
        string paragraph;
        while (getline (encryp_file, s)) {
        paragraph += s + "\n";
        if (s == "-----END PGP MESSAGE-----")   {
}
}
        encryp_file.close();
    
  const char *buf = paragraph.c_str();
  size_t nread=strlen(buf);
  cout << buf;
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
	
  write_data (out);
  
  gpgme_key_release (key);	
  gpgme_data_release (in);
  gpgme_data_release (out);
  gpgme_release (ctx);
  return 0;
}



int main () {
decrypt_file();
}
