#include "Socket.h"
#include "string.h"
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <iterator>

Socket::Socket() : m_sock(-1) { memset(&m_addr, 0, sizeof(m_addr)); }

Socket::~Socket() {
  if (is_valid()) {
    ::close(m_sock);
  }
}

bool Socket::create() {
  m_sock = socket(AF_INET, SOCK_STREAM, 0);

  if (!is_valid())
  {
    return false;
  }

  // TIME_WAIT - argh
  int on = 1;
  if (setsockopt(m_sock, 
      SOL_SOCKET, SO_REUSEADDR, 
      (const char *)&on,
      sizeof(on)) == -1)
  {
    return false;
  }

  return true;
}

bool Socket::bind(const int port) 
{
  if (!is_valid()) 
  {
    return false;
  }

  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons(port);

  auto bind_return = ::bind(m_sock, (struct sockaddr *)&m_addr, 
                            sizeof(m_addr));

  return bind_return != -1;
}

bool Socket::listen() const 
{
  if (!is_valid()) {
    return false;
  }

  auto listen_return = ::listen(m_sock, SocketConstants::MAXCONNECTIONS);

  return listen_return != -1;
}

bool Socket::accept(Socket &new_socket) const 
{
  auto addr_length = sizeof(m_addr);
  new_socket.m_sock =
      ::accept(m_sock, (sockaddr *)&m_addr, (socklen_t *)&addr_length);

  return new_socket.m_sock > 0;  
}

bool Socket::send(const std::string s) const 
{
  auto status = ::send(m_sock, s.c_str(), s.size(), MSG_NOSIGNAL);
  return status != -1;  
}

bool Socket::send(const std::vector<uchar> data) const
{
  auto status = ::send(m_sock, data.data(), data.size(), MSG_EOR);
  return status != -1;   
}

int Socket::recv(std::vector<uchar>& data) const
{
  
  uchar buff[SocketConstants::MB];  
  auto sum = 0;
  auto n = 0;  

  
  while(true) 
  {
    auto n = ::recv(m_sock, buff, SocketConstants::MB, 0);
    sum += n;
    data.insert( data.end(), std::begin(buff), std::end(buff) );
    
    if(n < SocketConstants::MB) {
      break;
    }
  } 
  
  return 0;
}

int Socket::recv(std::string &s) const {
  char buf[SocketConstants::MAXRECV + 1];
  s = "";
  memset(buf, 0, SocketConstants::MAXRECV + 1);

  auto status = ::recv(m_sock, buf, SocketConstants::MAXRECV, 0);

  if (status == -1) 
  {
    std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
    return 0;
  } 
  else if (status == 0) 
  {
    return 0;
  } else 
  {
    s = buf;
    return status;
  }
}

bool Socket::connect(const std::string host, const int port) {
  if (!is_valid())
  {
    return false;
  }

  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons(port);

  auto status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

  if (errno == EAFNOSUPPORT)
  {
    return false;
  }

  status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));
  return status == 0;  
}

void Socket::set_non_blocking(const bool b) {
  auto opts = fcntl(m_sock, F_GETFL);

  if (opts < 0) 
  {
    return;
  }

  opts = b ? (opts | O_NONBLOCK) : (opts & ~O_NONBLOCK);
  
  fcntl(m_sock, F_SETFL, opts);
}