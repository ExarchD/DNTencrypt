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
#include <thread>
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
	int threads = 10;
	std::thread myThreads[10];
	encryp_file.close();
	for (int j=0; j<threads; j++) {
	int begin=0;
	if (j != 0) begin=(j*enc_messages.size())/threads;
	int end=((j+1)*enc_messages.size())/threads;
        myThreads[j] = std::thread(thread_message_reader, enc_messages,begin,end);
}

        for (int j=0; j<threads; j++) {
	myThreads[j].join();
}
}


void thread_message_reader(vector<string> enc_messages, int begin, int end) {
        for ( int i=begin; i < end; i++){
        decrypter(enc_messages[i],true);
}

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
/*
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
*/
     message_reader();

	return 0;
}
