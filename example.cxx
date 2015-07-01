#include <iostream>
#include <iomanip>

#include "gpgme.h"

// Callback function to retrieve the passphrase
const char *myPass(void *hook, const char *desc, void **r_hd)
{
	char *sNull = "NULL";
	const char *p;
	if( desc ) p = desc;
	else p = sNull;

	std::cout << "myPass(" << p << ")" << std::endl;
	static const char *passPhrase = "secret";

	if( desc ) p = passPhrase;
	else p = NULL;

	return p;
}

int main(int argc, char *argv[])
{
	GpgmeCtx ctx;
	GpgmeData ciphertext, plaintext;
	GpgmeRecipients rset;

	gpgme_new (&ctx);
	gpgme_set_armor (ctx, 1);
	gpgme_set_passphrase_cb (ctx, myPass, NULL);

	char *plain = "Hallo Welt";

	gpgme_data_new_from_mem (&plaintext, plain, strlen(plain), 1 );
	std::cout << "gpgme_data_new_from_mem(plaintext) ok" << std::endl;

	GpgmeError err = gpgme_data_new ( &ciphertext );
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_data_new error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_data_new(cipher) ok" << std::endl;

	err = gpgme_recipients_new (&rset);
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_recipients_new error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_recipients_new() ok" << std::endl;

	err = gpgme_recipients_add_name (rset, "ne...@gmx.de");
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_recipients_add_name error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_recipients_add_name() ok" << std::endl;

	err = gpgme_op_encrypt (ctx, rset, plaintext, ciphertext );
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_op_encrypt error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_op_encrypt() ok" << std::endl;

	char buf[4096];
	size_t nread;
	err = gpgme_data_read( ciphertext, buf, sizeof(buf), &nread );
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_data_read error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_data_read() ok " << nread << " bytes" << std::endl;

	buf[nread] = 0;
	std::cout << buf;

	// free all used resources

	gpgme_data_release (plaintext);
	gpgme_data_release (ciphertext);
	gpgme_recipients_release (rset);

	//
	// Decrypt
	//
	err = gpgme_data_new_from_mem (&ciphertext, buf, nread, 1 );
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_data_new_from_mem(buf) error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_data_new_from_mem(ciphertext) ok" << std::endl;

	gpgme_data_new (&plaintext);
	err = gpgme_op_decrypt (ctx, ciphertext, plaintext);
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_op_decrypt error " << err << std::endl;
		exit(0);
	}
	std::cout << "gpgme_op_decrypt() ok" << std::endl;

	gpgme_data_release(ciphertext);

	err = gpgme_data_read( plaintext, buf, sizeof(buf), &nread );
	if( err != GPGME_No_Error )
	{
		std::cout << "gpgme_data_read error " << err << std::endl;
		exit(0);

	}
}
