#include "lib/ServerSocket.h"
#include "lib/SocketException.h"
#include <string>
#include <iostream>

int main ( int argc, int argv[] )
{
  std::cout << "running....\n";

    try
    {
      // Create the socket
        ServerSocket server ( 30000 );
        ServerSocket new_sock;
        server.accept ( new_sock );

        while(true)
        {
            try
            {
                while ( true )
                {
                    std::string data;
                    new_sock >> data;
                    new_sock << data;
                    
                }
            }
            catch ( SockException::SocketException& ) {}
	    }
    }
    catch ( SockException::SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}