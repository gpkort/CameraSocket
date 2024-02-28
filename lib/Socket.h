#pragma once

#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <vector>
#include <iostream>

namespace SocketConstants
{

constexpr int MAXHOSTNAME     =     200;
constexpr int MAXCONNECTIONS  =     5;
constexpr int MAXRECV         =     500;
constexpr int MB              =     16384;

constexpr char WRITING_TO_SOCKET_ERROR[]     = "Could not write to socket.";
constexpr char READING_FROM_SOCKET_ERROR[]   = "Could not read from socket.";
constexpr char PORT_BINDING_ERROR[]          = "Could not read from socket.";
constexpr char SOCKET_CREATE_ERROR[]         = "Could not create server socket.";

}

class Socket
{
 public:
    Socket();
    virtual ~Socket();

    // Server initialization
    bool create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( Socket& ) const;

    // Client initialization
    bool connect (const std::string host, const int port);

    // Data Transimission
    bool send(const std::string) const;
    bool send(const std::vector<uchar> data) const;

    int recv(std::string&) const;
    int recv(std::vector<uchar>& data) const;

    void set_non_blocking ( const bool );

    bool is_valid() const { return m_sock != -1; }

 private:
    int m_sock;
    sockaddr_in m_addr;
};
