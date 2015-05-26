#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include "objects.h"
#include <QApplication>
#include <mainwindow.h>
#include "passphrase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;



void message_reader() {
	vector<string> enc_messages;
	string line;
	ifstream encryp_file;
	encryp_file.open("messages.txt");
	string s;
	string paragraph;
	while (getline (encryp_file, s)) { 
	paragraph += s + "\n";
	if (s == "-----END PGP MESSAGE-----") 	{
	enc_messages.push_back(paragraph);
	paragraph.clear();
}
}
	encryp_file.close();

}

void message_writer(){
        ifstream encryp_file;
        encryp_file.open("messages.txt");
	// add in the write down part
        encryp_file.close();
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

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	
	return a.exec();
	return 0;
}
