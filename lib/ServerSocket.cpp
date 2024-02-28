// Implementation of the ServerSocket class

#include "ServerSocket.h"
#include "SocketException.h"


ServerSocket::ServerSocket ( int port )
{
  if (!Socket::create())
  {
    throw SockException::SocketException(SocketConstants::SOCKET_CREATE_ERROR);
  }

  if(!Socket::bind(port))
  {
    throw SockException::SocketException(SocketConstants::PORT_BINDING_ERROR);
  }

  if(!Socket::listen())
  {
    throw SockException::SocketException(SOCKET_LISTEN_ERROR);
  }

}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
  if (!Socket::send(s))
  {
    throw SockException::SocketException(SocketConstants::WRITING_TO_SOCKET_ERROR);
  }

  return *this;
}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
  if (!Socket::recv(s))
  {
    throw SockException::SocketException(SocketConstants::READING_FROM_SOCKET_ERROR);
  }

  return *this;
}

void ServerSocket::sendImage(cv::Mat frame)
{
  // Convert the frame to a JPEG image
  std::vector<uchar> encoded_frame;
  imencode(IMAGE_TYPE, frame, encoded_frame);  

  auto sz = encoded_frame.size();
  
  // Send the frame to the client
  if (!Socket::send(encoded_frame)) 
  { 
    throw SockException::CameraSocketException(IMAGE_SENDING_ERROR);
  }
}

void ServerSocket::accept ( ServerSocket& sock )
{
  if (!Socket::accept (sock))
  {
    throw SockException::SocketException("Could not accept socket.");
  }
}