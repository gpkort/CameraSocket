#pragma once

#include "Socket.h"
#include <opencv2/opencv.hpp>
#include <string>

constexpr char IMAGE_TYPE[] = ".jpg";
constexpr char IMAGE_SENDING_ERROR[] = "Error occured while Server sending image.";
constexpr char SOCKET_LISTEN_ERROR[] = "Could not listen to socket.";

class ServerSocket : private Socket
{
    public:
        ServerSocket ( int port );
        ServerSocket (){};
        virtual ~ServerSocket();

        const ServerSocket& operator << ( const std::string& ) const;
        const ServerSocket& operator >> ( std::string& ) const;

        void sendImage(cv::Mat frame);        

        void accept ( ServerSocket& );

};
