project(test)
cmake_minimum_required(VERSION 2.8)


# include *.h
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

# add src folder
aux_source_directory(src SRC_LIST)
aux_source_directory(. SRC_LIST)

# build flag
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -O0")
set(CMAKE_INSTALL_PREFIX ./)

# add folder of libs
link_directories("${CMAKE_SOURCE_DIR}/libs")

# add exe
add_executable(${PROJECT_NAME} ${SRC_LIST})


# link libs
TARGET_LINK_LIBRARIES(${PROJECT_NAME} event_core event_openssl -levent_extra -levent_pthreads -levent)



##############################################################
#              others                                        # 

# define
#add_definitions(-DJSON_IS_AMALGAMATION)

#SET(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_EXTENSIONS OFF)

# link libs
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
