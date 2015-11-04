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
}

int Conversation::retrieve ()
{

    while (running)
    {
    cout << running << endl;
    sleep(1);
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
