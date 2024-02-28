#include "ClientSocket.h"
#include "SocketException.h"


ClientSocket::ClientSocket(std::string host, int port)
{
    if (!Socket::create())
    {
        throw SockException::SocketException(SocketConstants::SOCKET_CREATE_ERROR);
    }

    if (!Socket::connect( host, port ) )
    {
        throw SockException::SocketException(SocketConstants::PORT_BINDING_ERROR);
    }
}


const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    if (!Socket::send(s))
    {
        throw SockException::SocketException(SocketConstants::WRITING_TO_SOCKET_ERROR);
    }
    return *this;
}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
  if (!Socket::recv(s))
  {
    throw SockException::SocketException(SocketConstants::READING_FROM_SOCKET_ERROR);
  }

  return *this;
}

cv::Mat ClientSocket::recvImage() const
{
  std::vector<uchar> buffer; 
  auto status = Socket::recv(buffer);
  auto sz = buffer.size();

  if(status != 0)
  {
    throw SockException::SocketException(READING_FROM_CAMERA_SOCKET_ERROR);
  }

  auto image = cv::imdecode(buffer, cv::IMREAD_COLOR);  

  if (image.empty()) 
  {
      throw SockException::SocketException(EMPTY_IMAGE_CAMERA_SOCKET_ERROR);  
  }

  std::cout << "image rows:" << image.rows << ", cols: " << image.cols << std::endl;

  return image;  

}