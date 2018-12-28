project(test)
cmake_minimum_required(VERSION 2.8)

# add src folder
aux_source_directory(. SRC_LIST)

# build flag
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -O0")
set(CMAKE_INSTALL_PREFIX ./)

# add exe
add_executable(${PROJECT_NAME} ${SRC_LIST})

# add folder of libs
#link_directories("/usr/lib64/")

# add folder of include
include_directories(/usr/include/gtk-3.0 /usr/include/freetype2) 
include_directories(/usr/include/pango-1.0 /usr/include/libpng16) 
include_directories(/usr/include/glib-2.0 /usr/include/libdrm) 
include_directories(/usr/lib64/glib-2.0/include /usr/include/harfbuzz) 
include_directories(/usr/include/cairo /usr/include/gdk-pixbuf-2.0) 
include_directories(/usr/include/pixman-1 /usr/include/gio-unix-2.0) 
include_directories(/usr/include/at-spi-2.0 /usr/include/dbus-1.0) 
include_directories(/usr/lib64/dbus-1.0/include /usr/include/atk-1.0) 

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lglib-2.0 atk-1.0)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpthread cairo-gobject)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lgtk-3 cairo)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lgdk-3 gdk_pixbuf-2.0)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpangocairo-1.0 gio-2.0)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpango-1.0 gobject-2.0)

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
