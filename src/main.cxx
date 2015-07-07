#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <QApplication>
#include <mainwindow.h>
#include "passphrase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unistd.h>
//#include <thread>
#include "objects.h"

using namespace std;
string user_email;
string server_ip;
int debug;

void store_line(string key, string value) {
    if (key == "user_email") user_email=value;
    if (key == "server_ip") server_ip=value;
    cout << key <<" " << value  << endl;
}

void set_serverip(std::string serverip) 
{
        server_ip=serverip;
            store_line(server_ip,serverip);
}

void config_edit(string key_new, string value_new) {
    ifstream iconf;
    iconf.open("config.txt");
    ofstream oconf;
    oconf.open("config_tmp.txt");
    string line;
    string strTemp;
    store_line(key_new, value_new);
    while(iconf >> strTemp)
    {
     string key;
     key = strTemp.substr(0, strTemp.find("="));
        cout << key  << " " << key_new << endl;
        if(key == key_new){
            strTemp = key_new+"="+value_new;
        }
        strTemp += "\n";
        oconf << strTemp;
        rename("config_tmp.txt","config.txt");
}
    oconf.close();
    iconf.close();
}



void encrypt2_init() {
    ifstream conf;
    string line;
    conf.open("config.txt");
    cout << "LOADING CONFIG" << endl;
    while (getline (conf, line))
           {
             istringstream is_line(line);
             string key;
             if( getline(is_line, key, '=') )
             {
               string value;
               if( getline(is_line, value) )
                 store_line(key, value);
             }
           }
    conf.close();
    cout << "CONFIG LOADED" << endl;
}
/*
void thread_message_reader(vector<string> enc_messages, int begin, int end) {
        for ( int i=begin; i < end; i++){
        decrypter(enc_messages[i],true);
}

}

void thread_message_reader2(vector<string> enc_messages, int begin, int end) {
        for ( int i=begin; i < end; i++){
        decrypter2(enc_messages[i],true);
}

}
*/
/*
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

	int threads = 1;
	std::thread myThreads[3];
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
*/

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
debug = 2;
init_gpgme (GPGME_PROTOCOL_OpenPGP);
    //encrypt2_init();
    if (debug == 1 ) cout << "encryption initialized" << endl;
	QApplication a(argc, argv);
    MainWindow w;
    if (debug == 1 ) cout << "main window loaded" << endl;
	w.show();
	return a.exec();
    if (debug == 1 ) cout << "closing..." << endl;

//     message_reader();

	return 0;
}
