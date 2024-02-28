cmake_minimum_required(VERSION 3.10)

project(SocketSock VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file( GLOB LIB_SOURCES lib/*.cpp )
file( GLOB LIB_HEADERS lib/*.h )
add_library( SocketSockLib ${LIB_SOURCES} ${LIB_HEADERS} )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(OPENCV_LIB_DIRS /usr/local/lib/)
add_definitions(-w)
target_link_libraries(SocketSockLib ${OPENCV_LIB_DIRS}libopencv_imgproc.so)
target_link_libraries(SocketSockLib ${OPENCV_LIB_DIRS}libopencv_imgcodecs.so)
target_link_libraries(SocketSockLib ${OPENCV_LIB_DIRS}libopencv_core.so)
target_link_libraries(SocketSockLib ${OPENCV_LIB_DIRS}libopencv_videoio.so)
target_link_libraries(SocketSockLib ${OPENCV_LIB_DIRS}libopencv_highgui.so)

# add the executables
add_executable(SocketServer simple_server.cpp)
target_link_libraries(SocketServer SocketSockLib)

add_executable(SocketClient simple_client.cpp)
target_link_libraries(SocketClient SocketSockLib)

add_executable(CameraServer camera_server.cpp)
target_link_libraries(CameraServer SocketSockLib)

add_executable(CameraClient camera_client.cpp)
target_link_libraries(CameraClient SocketSockLib)



# opencv_highgui

