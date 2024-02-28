#include "lib/ServerSocket.h"
#include "lib/SocketException.h"
#include <string>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio/videoio.hpp"


int main ( int argc, char **argv )
{
  std::cout << "running....\n";

    try
    {
      // Create the socket
      ServerSocket server(30000);
      ServerSocket new_sock;
      server.accept(new_sock);

      cv::VideoCapture cap(0);
      
      if (!cap.isOpened()) 
      {
        std::cout << "Error opening camera" << std::endl;
        return -1;
      }
      else
      {
        std::cout << "Camera is open!" << std::endl;
      }


      while(true)
      { 
        try
        {          
          std::cout << "Starting while...." << std::endl;
          
          cv::Mat frame;
          // cap >> frame;
          cap.read(frame);

          if(frame.empty()) 
          {
            std::cout << "Frame was empty" << std::endl;
            break;
          }  
                  
          new_sock.sendImage(frame);  
          std::cout << "Done sending";

        }
        catch(SockException::SocketException& e) {
          std::cout << "Exception was inner caught:" << e.description() << "\nExiting.\n";
          break;
        }
	    }      
    }
    catch(SockException::SocketException& e)
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    
    return 0;
}