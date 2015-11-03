#ifndef TELECHARGER_HPP
#define TELECHARGER_HPP
 
 
#include <iostream>
#include <string>
 
    int check_serverstatus(const char* host_int, int port_int);
    int sender(const char* host_int, int port_int, const char* msg, int length);
 
#endif /* TELECHARGER_HPP */
