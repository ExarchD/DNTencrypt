#include <conversation.h> 
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <thread>
using namespace std;


Conversation::Conversation ()
{
    running=false;
}

int Conversation::send (vector<string> recipients, string msg)
{
    cout << msg << endl;
    return 0;
}

void Conversation::init ()
{
    running=true;
    /* vector<conversation_list> myconvos; */
    conversation_list vide_convo;
    vide_convo.hash="hash";
    vide_convo.salt="salt";
    vide_convo.urgency=1;
    vide_convo.iterator=1;
    myconvos.push_back(vide_convo);

}

int Conversation::retrieve ()
{

    int counter = 0;
    while (running)
    {
        counter++;
        cout << counter << endl;
        sleep(1);
        for ( int cons =0; cons < myconvos.size(); cons++)
        {
            if (myconvos[cons].urgency == 1) {
                if ( counter % 1 == 0 ) cout << "Every second" << endl;
            }
            if (myconvos[cons].urgency == 2) {
                if ( counter % 20 == 0 ) cout << "Every twenty seconds" << endl;
            }
            if (myconvos[cons].urgency == 3) {
                if ( counter % 30 == 0 ) cout << "Every thirty seconds" << endl;
            }
            if (myconvos[cons].urgency == 4) {
                if ( counter % 300 == 0 ) cout << "Every five minutes" << endl;
            }
        }
        if ( counter == 300 ) counter = 0;
    }


    return 1;
}


void Conversation::startretrieve ()
{
    t1=std::thread (&Conversation::retrieve, this);
}

void Conversation::endretrieve ()
{
    running=0;
    t1.join();
}
