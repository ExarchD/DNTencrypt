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
    vide_convo.noresponse=0;
    myconvos.push_back(vide_convo);

}

int Conversation::retrieve_thread ()
{

    int counter = 0;
    while (running)
    {
        counter++;
        cout << counter << endl;
        sleep(1);
        for ( int cons =0; cons < myconvos.size(); cons++)
        {
            cout << myconvos[cons].urgency << endl;
            if ( counter % myconvos[cons].urgency == 0 ) 
            {
                cout << "Every " << myconvos[cons].urgency << " seconds" << endl;
                /* if (!send(retrieval) */
                myconvos[cons].noresponse++;
                if (myconvos[cons].noresponse > 5)
                {
                    if (myconvos[cons].urgency == 60)
                        myconvos[cons].urgency=300;
                    if (myconvos[cons].urgency == 30)
                        myconvos[cons].urgency=60;
                    if (myconvos[cons].urgency == 15)
                        myconvos[cons].urgency=30;
                    if (myconvos[cons].urgency == 5)
                        myconvos[cons].urgency=15;
                    if (myconvos[cons].urgency == 1)
                        myconvos[cons].urgency=5;
                    myconvos[cons].noresponse=0;

                }

            }
        }
        if ( counter == 300 ) counter = 0;
    }


    return 1;
}


void Conversation::startretrieval_thread ()
{
    t1=std::thread (&Conversation::retrieve_thread, this);
}

void Conversation::endretrieval_thread ()
{
    running=0;
    t1.join();
}
