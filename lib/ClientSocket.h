#pragma once

#include "Socket.h"

constexpr char READING_FROM_CAMERA_SOCKET_ERROR[] = "Could not read image from socket.";
constexpr char EMPTY_IMAGE_CAMERA_SOCKET_ERROR[] = "Received from empty image from socket.";

class ClientSocket : private Socket
{
    public:

        ClientSocket ( std::string host, int port );
        virtual ~ClientSocket(){};

        const ClientSocket& operator << ( const std::string& ) const;
        const ClientSocket& operator >> ( std::string& ) const;

        cv::Mat recvImage() const;
};
