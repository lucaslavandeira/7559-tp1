#ifndef ROUTE_H
#define ROUTE_H

#include <string>

#define BYTES_RECEIVE 50

class Route {
    int pipefds[2]{};
    std::string eof_msg;
public:
    /*
    Creates a pipe with eof_msg being the message returned when EOF is read
    */
    Route(std::string eof_msg);
    /*
    Sends a string "msg" of size "size" through the pipe
    */    
    void send(const std::string &msg, size_t size);
    /*
    Receives a string from the pipe
    */    
    std::string receive();
    ~Route();

private:
    /*
    Creates the pipe
    */
    void create_route();

};

#endif
