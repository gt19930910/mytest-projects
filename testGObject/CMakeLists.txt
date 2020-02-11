project(test)
cmake_minimum_required(VERSION 2.8)

# include *.h
INCLUDE_DIRECTORIES(src)

# add src folder
aux_source_directory(src SRC_LIST)
aux_source_directory(. SRC_LIST)

# build flag
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -O0")
set(CMAKE_INSTALL_PREFIX ./)

INCLUDE_DIRECTORIES(
    /usr/include
    /usr/include/glib-2.0
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
    /usr/include/gtk-3.0/
    /usr/include/pango-1.0
    /usr/include/cairo
    /usr/include/gdk-pixbuf-2.0
    /usr/include/gio-unix-2.0/
    /usr/include/atk-1.0
)

# add exe
add_executable(${PROJECT_NAME} ${SRC_LIST})

# add folder of libs
#link_directories("/usr/lib64/")

set(VCD_LINK_LIB
-lgthread-2.0
-lz
-lpixman-1
-lgtk-3
-lgdk-3
-lpangocairo-1.0
-lpango-1.0
-lcairo-gobject
-lcairo
-lgdk_pixbuf-2.0
-lepoxy
-lpthread
-lgio-2.0
-lgobject-2.0
-lglib-2.0
-lm
-lgmodule-2.0
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VCD_LINK_LIB})

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
#install(TARGETS ${PROJECT_NAME} DESTINATION lib64)
#install(FILES ${EXPORT_INCLUDE} DESTINATION include)

##############################################################
