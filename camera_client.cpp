#include "lib/ClientSocket.h"
#include "lib/SocketException.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, int argv[])
{
    try 
    {
      ClientSocket client_socket("localhost", 30000);
      while(true)
      {
        
        cv::Mat img;

        auto image = client_socket.recvImage();
        cv::imshow("Image", image);  
        cv::waitKey(100);
      }
    }
    catch(SockException::SocketException& e)
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }    
 
    return 0;
}