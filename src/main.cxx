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
#include <thread>
#include "objects.h"
#include <csignal>
#include "sha1.h"
#include "telecharger.h"


using namespace std;
string user_email;
string server_ip;
int port_value;
bool configfileexist;
int debug;
int msg_index;
vector<convo> conversations;


void store_line(string key, string value) {
    if (key == "user_email") user_email=value;
    if (key == "server_ip") server_ip=value;
    /* if (key == "port") port_value=std::stoi(value); */
    /* if (key == "debug") debug=std::stoi(value); */
}


void main_encrypter(vector<std::string> recipients, string msg)
{
    /* message_type current_msg = encrypter(recipients, msg); */
    /* loop over conversations, if there is a match, then */ 
    /* try to send by iterating the iter value and sending */
    /* if we fail, then iterate again and send again, repeat */ 
    /* until successful. */ 
    /* If there is no hash match, then send a convo init message */
    /* then send actual message */

    message_type current_message = encrypter(recipients, msg);
    string message_key = current_message.pre_hash;
    cout << message_key << endl;
    string b = current_message.message;
    cout << b << endl;
    string recipts_key = current_message.recipients;
    cout << recipts_key << endl;


    cout << conversations.size() << endl;
    bool match = 0;
    for ( int x =0; x < conversations.size(); x++ )
    {
        if (sha1(message_key) == conversations[x].hash) 
        {
            cout << "matched" << endl;
            match = 1;
            while (true){
                string full_msg_key=message_key+to_string(msg_index);
                string parsedmsg = "0;"+sha1(full_msg_key)+";"+b+";"+recipts_key; 
                conversations[x].iterator++;
                if (sender(server_ip.c_str(), port_value, msg.c_str(), 512))
                    break;
            }

        }
    }
    if (!match) {
            cout << "unmatched" << endl;
        convo newconvo;
        newconvo.hash=sha1(message_key);
        newconvo.iterator=1;
        conversations.push_back(newconvo);
    }
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
        if (debug > 3) cout << key_new  << " " << value_new << endl;
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
    string line;
    if (std::ifstream("config.txt"))
    {
        configfileexist=true;
        ifstream conf;
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
                    cout << key << " set to: " << value << endl;
                store_line(key, value);
            }
        }
        cout << "CONFIG LOADED" << endl;
    }
    else 
    {
        cout << "creating config file" << endl;
        configfileexist=false;
        ofstream myfile;
        myfile.open ("config.txt");
        myfile << "port=\nserver_ip=\nuser_email=\n";
        myfile.close();

    }
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
    // do all the necessary closing things
    // shifting messages to long term storage, re-encrypting databases
    // collecting threads
    
    cout << "saving convos" << endl;
    save_convos(conversations);
    cout << "exiting" << endl;
    exit(0);
}

void retrieve() {
    while (1) {
        std::cout << "waiting 2 seconds" << std::endl;
        sleep(2);
    }
}


void signalHandler( int signum )
{
    cout << "Interrupt signal (" << signum << ") received.\n";

    exit_program();
    //   exit(signum);  

}



int main (int argc, char* argv[] ) {
    signal(SIGINT, signalHandler); 
    debug = 2;
    init_gpgme (GPGME_PROTOCOL_OpenPGP);
    encrypt2_init();

    if (debug > 1 ) cout << "encryption initialized" << endl;
    //        std::thread(thread_message_reader, enc_messages,begin,end);
    //     string ret_message="1;7e72f698584929fb8523825b7a2da3a6a616839b;ec5f6dcd77ab7e60df700e682dd89113f6b1186c";
    //       sender(server_ip.c_str(), 6655, ret_message.data(), 5000);


    /* cout << check_serverstatus(server_ip.c_str(),port_value) << endl; */
    cout << "starting" << endl;
    /* qrecord("Key","Value"); */
    /* conversations=load_convos(); */
    /* convo blank; */
    /* blank.hash="zip"; */
    /* blank.iterator=0; */
    /* conversations.push_back(blank); */
    /* load_convos(); */
    QApplication a(argc, argv);
    MainWindow w;
    if (debug > 1 ) cout << "main window loaded" << endl;
    w.show();
    return a.exec();
    if (debug > 1 ) cout << "closing..." << endl;

    return 0;
}
