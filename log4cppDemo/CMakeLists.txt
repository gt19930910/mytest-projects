project(test)
cmake_minimum_required(VERSION 2.8)


# include *.h
INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/log4cpp/include)


# add src folder
aux_source_directory(src SRC_LIST)
aux_source_directory(. SRC_LIST)

# build flag
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -O0")
set(CMAKE_INSTALL_PREFIX ./)


# add folder of libs
link_directories("${CMAKE_SOURCE_DIR}/src/log4cpp")
# add exe
add_executable(${PROJECT_NAME} ${SRC_LIST})

# link libs
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -llog4cpp -lpthread)



##############################################################
#              others                                        # 

#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

# define
#add_definitions(-DJSON_IS_AMALGAMATION)

#SET(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_EXTENSIONS OFF)

# link libs
link_directories("${CMAKE_SOURCE_DIR}/src/ffmpeg/libs")
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lglib-2.0)

# export *.h
#set(EXPORT_INCLUDE src/adapter/include/export_header.h)

# lib
#ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRC_LIST})  #make shared lib
#ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_LIST})  #make static lib

#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wno-write-strings -Wno-narrowing")

# install
install(TARGETS ${PROJECT_NAME} DESTINATION lib64)
install(FILES ${EXPORT_INCLUDE} DESTINATION include)

##############################################################
