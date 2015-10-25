cmake_minimum_required(VERSION 3.3)
project(TP1_Recsys)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
FIND_PACKAGE ( Threads REQUIRED )

set(SOURCE_FILES Constants.h main.cpp CSVReader.cpp CSVReader.h StringUtils.cpp StringUtils.h
        ReadInputs.cpp ReadInputs.h ArrayUtils.h ArrayUtils.cpp DebugUtils.cpp DebugUtils.h
        ItemContent.cpp ItemContent.h)
add_executable(recommender ${SOURCE_FILES})
TARGET_LINK_LIBRARIES ( recommender ${CMAKE_THREAD_LIBS_INIT} )
