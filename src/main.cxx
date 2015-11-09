#include <ext/alloc_traits.h>  // for __alloc_traits<>::value_type
#include <mainwindow.h>        // for MainWindow
#include <qrecorder.h>        // for MainWindow
#include <QApplication>      // for QApplication
#include <stdio.h>             // for rename
#include <stdlib.h>            // for exit
#include <unistd.h>            // for sleep
#include <csignal>             // for signal
#include <iostream>            // for operator<<, basic_ostream, cout, etc
#include <string>              // for string, operator+, operator<<, etc
#include <vector>              // for allocator, vector
#include "conversation.h"      // for Conversation
#include "encrypter.h"         // for encrypter, init_gpgme
#include "gpgme.h"             // for ::GPGME_PROTOCOL_OpenPGP
#include "objects.h"           // for convo, message_type, save_convos
#include "sha1.h"              // for sha1
#include "telecharger.h"       // for sender
#include <fstream>
#include <sstream>

/* #ifdef HAVE_CONFIG_H */
/* #include <config.h> */
/* #endif */

using namespace std;
string user_email;
Conversation convos;
string server_ip;
int port_value;
bool configfileexist;
int debug;
int msg_index;
vector<convo> conversations;


void main_encrypter(vector<std::string> recipients, string msg)
{
    /* message_type current_msg = encrypter(recipients, msg); */
    /* loop over conversations, if there is a match, then */ 
    /* try to send by iterating the iter value and sending */
    /* if we fail, then iterate again and send again, repeat */ 
    /* until successful. */ 
    /* If there is no hash match, then send a convo init message */
    /* then send actual message */

    /* message_type current_message = encrypter(recipients, msg); */
    /* string message_key = current_message.pre_hash; */
    /* cout << message_key << endl; */
    /* string b = current_message.message; */
    /* cout << b << endl; */
    /* string recipts_key = current_message.recipients; */
    /* cout << recipts_key << endl; */


    /* cout << conversations.size() << endl; */
    /* bool match = 0; */
    /* for ( int x =0; x < conversations.size(); x++ ) */
    /* { */
    /*     if (sha1(message_key) == conversations[x].hash) */ 
    /*     { */
    /*         cout << "matched" << endl; */
    /*         match = 1; */
    /*         while (true){ */
    /*             string full_msg_key=message_key+to_string(msg_index); */
    /*             string parsedmsg = "0;"+sha1(full_msg_key)+";"+b+";"+recipts_key; */ 
    /*             conversations[x].iterator++; */
    /*             if (sender(server_ip.c_str(), port_value, msg.c_str(), 512)) */
    /*                 break; */
    /*         } */

    /*     } */
    /* } */
    /* if (!match) { */
    /*         cout << "unmatched" << endl; */
    /*     convo newconvo; */
    /*     newconvo.hash=sha1(message_key); */
    /*     newconvo.iterator=1; */
    /*     conversations.push_back(newconvo); */
    /* } */
}
void message_writer(){
    ifstream encryp_file;
    encryp_file.open("messages.txt");
    // add in the write down part
    encryp_file.close();
}

int exit_program() {
    cout << "joining threads" << endl;
    convos.endretrieval_thread();
    cout << "saving convos" << endl;
    convos.csave_convos();
    /* save_convos(conversations); */
    cout << "exiting" << endl;
    exit(0);
}


void signalHandler( int signum )
{
    cout << "Interrupt signal (" << signum << ") received.\n";

    exit_program();

}


int main (int argc, char* argv[] ) {
    signal(SIGINT, signalHandler); 
    init_gpgme (GPGME_PROTOCOL_OpenPGP);

    if (debug > 1 ) cout << "encryption initialized" << endl;

    cout << "starting conversation object" << endl;

    convos.cload_convos();
    QApplication a(argc, argv);
    MainWindow w(&convos);
    if (debug > 1 ) cout << "main window loaded" << endl;
    w.show();
    return a.exec();
    if (debug > 1 ) cout << "closing..." << endl;

    return 0;
}
