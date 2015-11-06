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
    vide_convo.salt="a348ec8d18e,+&=First chat";
    vector<string> emails;
    emails.push_back("pluthd@gmail.com");
    vide_convo.recipients=emails;
    myconvos.push_back(vide_convo);
    myconvos_intime=myconvos;


}

int Conversation::retrieve_thread ()
{

    int counter = 0;
    while (running)
    {
        counter++;
        /* cout << counter << endl; */
        sleep(1);
        for ( int cons =0; cons < myconvos.size(); cons++)
        {
            /* cout << myconvos[cons].urgency << endl; */
            if ( counter % myconvos[cons].urgency == 0 ) 
            {
                /* cout << myconvos[cons].salt <<  "Every " << myconvos[cons].urgency << " seconds" << endl; */
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
    conversationItem vide_convo;
    /* vide_convo.urgency=1; */
    /* vide_convo.noresponse=0; */
    /* vide_convo.iterator=1; */
    /* vide_convo.salt="a348ec8d18e,+&=First chat"; */
    /* vector<string> emails; */
    /* emails.push_back("pluthd@gmail.com"); */
    /* vide_convo.recipients=emails; */
    /* myconvos.push_back(vide_convo); */
    /* for ( int mem=0; mem<recipients.size(); mem++) */
    /* { */
    /*     /1* send message to each member of the conversation with *1/ */
    /*     /1* the salt, the members, etc etc *1/ */
    /* } */
    conversationItem created;
    created.urgency=1;
    created.noresponse=0;
    created.iterator=1;
    created.salt=salt+",+&="+name;
    created.recipients=recipients;

    myconvos.push_back(created);

}


vector<Conversation::gui_convo> Conversation::list_convos ()
{

    vector<gui_convo> n;
    for ( int cons =0; cons < myconvos.size(); cons++)
    {
        std::string s=myconvos[cons].salt;
        std::string delimiter = ",+&=";
        std::string token = s.substr(0, s.find(delimiter)); 
        gui_convo mygui_convo;
        mygui_convo.name=token;
        mygui_convo.recipients=myconvos[cons].recipients;
        n.push_back(mygui_convo);
    }

    return n;
}

vector<Conversation::gui_convo> Conversation::list()
{
    vector<gui_convo> n;
    for ( int cons =0; cons < myconvos.size(); cons++)
    {
        std::string s=myconvos[cons].salt;
        std::string delimiter = ",+&=";
        s.erase(0, s.find(delimiter)+delimiter.length());
        /* std::string token = s.substr(0, s.find(delimiter)); */ 
        gui_convo mygui_convo;
        mygui_convo.name=s;
        mygui_convo.recipients=myconvos[cons].recipients;
        n.push_back(mygui_convo);
    }

    return n;
}

