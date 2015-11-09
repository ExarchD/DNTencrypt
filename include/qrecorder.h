#ifndef QRECORDER_HPP
#define QRECORDER_HPP

#include <string>
#include <vector>
#include <objects.h>

using namespace std;
class Qrecorder
{
public:
    Qrecorder();
 
private:
void qsetvalue (QString key);
void qconvo(std::string convolog, int itr) ;
};
void load_config ();
void qrecord(std::string key_new, std::string value_new) ;
std::vector <convo> load_convos ();
void save_convos( vector<convo> savelist);

#endif /* QRECORDER_HPP */
