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
    conversationItem vide_convo;
    vide_convo.urgency=1;
    vide_convo.noresponse=0;
    vide_convo.iterator=1;
    vide_convo.salt="a348ec8d18e,First chat";
    vector<string> emails;
    emails.push_back("pluthd@gmail.com");
    vide_convo.recipients=emails;
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

int Conversation::add (std::vector<std::string> recipients, std::string salt, std::string name)
{
    conversationItem created;
    created.urgency=1;
    created.noresponse=0;
    created.iterator=1;
    created.salt=salt+",+&="+name;
    created.recipients=recipients;

    for ( int mem=0; mem<recipients.size(); mem++)
    {
        /* send message to each member of the conversation with */
        /* the salt, the members, etc etc */
    }

}


vector<Conversation::gui_convo> Conversation::list_convos ()
{

    vector<gui_convo> n;
    for ( int con_itr=0; con_itr<myconvos.size(); con_itr++)
    {
        std::string s=myconvos[con_itr].salt;
        std::string delimiter = ",+&=";
        std::string token = s.substr(0, s.find(delimiter)); 
        gui_convo mygui_convo;
        mygui_convo.name=token;
        mygui_convo.recipients=myconvos[con_itr].recipients;
        n.push_back(mygui_convo);
    }

    return n;
}

