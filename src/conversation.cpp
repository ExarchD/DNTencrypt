#include <conversation.h> 
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <thread>
#include <sha1.h>
#include <encrypter.h>

using namespace std;


Conversation::Conversation ()
{
    running=false;
}

int Conversation::send (vector<string> recipients, string msg)
{

    message_type enc_msg=encrypter(recipients, msg);
    for (int x=0; x < enc_msg.members.size(); x++)
    {


    }
    return 0;
}

void Conversation::init ()
{
    running=true;
    /* conversationItem vide_convo; */
    /* vide_convo.urgency=1; */
    /* vide_convo.noresponse=0; */
    /* vide_convo.iterator=1; */
    /* vide_convo.salt="a348ec8d18e,+&=First chat"; */
    /* vector<string> emails; */
    /* emails.push_back("pluthd@gmail.com"); */
    /* vide_convo.recipients=emails; */
    /* myconvos.push_back(vide_convo); */
    /* myconvos_intime=myconvos; */


}

int Conversation::retrieve_thread ()
{

    int counter = 0;
    while (running)
    {
        counter++;
        sleep(1);
        for ( int cons =0; cons < myconvos.size(); cons++)
        {
            if ( counter % myconvos[cons].urgency == 0 ) 
            {
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
    conversationItem created;
    created.urgency=1;
    created.noresponse=0;
    created.iterator=1;
    created.salt=salt;
    created.name=name;
    created.recipients=recipients;
    string idhash= sha1(salt+",+&="+name);
    created.idhash=idhash;

    myconvos.push_back(created);

}


vector<Conversation::gui_convo> Conversation::list()
{
    vector<gui_convo> n;
    for ( int cons =0; cons < myconvos.size(); cons++)
    {
        std::string s=myconvos[cons].salt;
        std::string delimiter = ",+&=";
        s.erase(0, s.find(delimiter)+delimiter.length());
        gui_convo mygui_convo;
        mygui_convo.name=s;
        mygui_convo.id=myconvos[cons].idhash;
        mygui_convo.recipients=myconvos[cons].recipients;
        n.push_back(mygui_convo);
    }

    return n;
}

void Conversation::csave_convos()
{
    std::vector<enc_convo> allenc_msg;
    for (int x=0; x < myconvos.size(); x++) 
    {
        enc_convo newenc;
        newenc.urgency=myconvos[x].urgency;
        newenc.noresponse=myconvos[x].urgency;
        newenc.iterator=myconvos[x].iterator;
        string unency=myconvos[x].salt;
        for ( int y=0; y < myconvos[x].recipients.size(); y++)
        {
            unency+="$@@&;";
            unency+=myconvos[x].recipients[y];
        }
        vector<string> stringrec;
        message_type tempmes=encrypter(stringrec, unency);
        newenc.enc_info=tempmes.message;
        allenc_msg.push_back(newenc);
    }
    record_convos(allenc_msg);
}

void Conversation::cload_convos()
{
    std::vector<enc_convo> allenc_msg=load_convos();
    conversationItem vide_convo;
    for (int x=0; x < allenc_msg.size(); x++)
    {
        vide_convo.iterator=allenc_msg[x].iterator;
        vide_convo.urgency=allenc_msg[x].urgency;
        vide_convo.noresponse=allenc_msg[x].noresponse;
        string unencyp=decrypter(allenc_msg[x].enc_info, 0);
        string delimiter="$@@&;";
        string s=unencyp;
        size_t pos = s.find(delimiter);
        vide_convo.salt=s.substr(0, pos);
        s.erase(0, s.find(delimiter)+delimiter.length());
        std::vector<std::string> recipients;
        string srecipt=s;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            recipients.push_back(token);
            s.erase(0, pos + delimiter.length());

        }
        recipients.push_back(s);
        vide_convo.recipients=recipients;

        myconvos.push_back(vide_convo);
    }
}
