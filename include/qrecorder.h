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
    /** 
     * @brief Sets value from config file globally
     * 
     * @param key The key to act on
     */
void qsetvalue (QString key);
/** 
 * @brief Nothing yet, will hold conversations...need to consider how this will be handled
 * 
 * @param convolog
 * @param itr
 */
void qconvo(std::string convolog, int itr) ;
};
/** 
 * @brief Retrieves server addr and other variables from the config file
 */
void load_config ();
/** 
 * @brief Records new info into config file
 * 
 * @param key_new The new key for a variable
 * @param value_new The new value for key_new
 */
void qrecord(std::string key_new, std::string value_new) ;
/* std::vector <convo> load_convos (); */

#endif /* QRECORDER_HPP */
