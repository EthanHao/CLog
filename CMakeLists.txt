project (CLOG)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#head file path
INCLUDE_DIRECTORIES(./include)
#source directory
AUX_SOURCE_DIRECTORY(src CPP_FILES)


#print the direcories
MESSAGE(STATUS "CPP_FILES: " ${CPP_FILES})
MESSAGE(STATUS "Binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "Source dir: " ${PROJECT_SOURCE_DIR})

add_Library (CLOG STATIC ${CPP_FILES})

TARGET_LINK_LIBRARIES( CLOG
pthread
)
