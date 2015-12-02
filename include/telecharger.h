#ifndef TELECHARGER_HPP
#define TELECHARGER_HPP
 
 
#include <iostream>
#include <string>
 
/** 
 * @brief Will check the status of the server at start up and whenever there seems to be a disconnect
 * 
 * @param host_int
 * @param port_int
 * 
 * @return 
 */
    int check_serverstatus(const char* host_int, int port_int);
    /** 
     * @brief Handles sending "messages" to the server
     * 
     * @param host_int The server's address
     * @param port_int The server's active port
     * @param msg The message itself, encrypted or just hashes
     * @param length Always set to 512, decent packet size
     * 
     * @return 
     */
    int sender(const char* host_int, int port_int, const char* msg, int length);
 
#endif /* TELECHARGER_HPP */
