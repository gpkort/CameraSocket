#include "lib/ClientSocket.h"
#include "lib/SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, int argv[] )
{
    try
    {
        ClientSocket client_socket ( "localhost", 30000 );
        std::string reply;

        try
        {
            client_socket << "Test message.";
            client_socket >> reply;
        }
        catch ( SockException::SocketException& ) {}

        std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
    }
    catch ( SockException::SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }
    return 0;
}