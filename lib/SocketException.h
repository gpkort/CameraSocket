#pragma once

#include <string>

namespace SockException
{

class SocketException
{
 public:
    SocketException (std::string s) : m_s(s) {};
    ~SocketException (){};

    std::string description() { return m_s; }

 private:
    std::string m_s;
};


class CameraSocketException : public SocketException
{
   public:
      CameraSocketException(std::string s) : SocketException(s) {}
};

}
