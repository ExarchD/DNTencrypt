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
    /* cout << "Init" << endl; */
    /* sleep(1); */
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


/* void Conversation::startretrieve (Conversation co) */
/* { */
/*     /1* std::vector<std::string> test; *1/ */
/*     /1* test.push_back("1"); *1/ */
/*     /1* test.push_back("2"); *1/ */
/*     /1* int (Conversation::*retobj)(std::vector<std::string>); *1/ */
/*     /1* retobj=&Conversation::retrieve; *1/ */
/*     /1* thread first (retobj, test); *1/ */


/* } */


void Conversation::startretrieve2 ()
{
    t1=std::thread (&Conversation::retrieve, this);
    /* t1.join(); */
}

void Conversation::endretrieve ()
{
    t1.join();
}
