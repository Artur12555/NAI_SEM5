cmake_minimum_required(VERSION 3.23)
project(NAI_SEM5)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab7 lab7/lab7.cpp)

# UWAGA: TU ZAMIEN KATALOG W KTORYM JEST OPENCV!!!!
set(OpenCV_DIR "C:\\Users\\czarn\\Documents\\repozytorium\\opencv-4.x\\cmake-build-release")

find_package( OpenCV REQUIRED )

if( OpenCV_FOUND )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
    link_directories( ${OpenCV_LIB_DIR} )
    #target_link_libraries( ocvdemo ${OpenCV_LIBS} ) # - to jest wersja dzialajaca na linux, ale nie na windows

    target_link_libraries( lab7 opencv_core;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_videoio )
endif()