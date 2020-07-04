cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(GeometryLibProj)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "libs")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo" CACHE STRING "" FORCE)
set(DEBUG_CONFIGURATIONS "Debug;RelWithDebInfo")

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox /Ob2 /Oi /Ot /Oy /GT")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /wd4018 /wd4996 /wd4244") # ignore signed/unsigned comparison
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Werror -Wall -Wno-comment -Wextra -Wno-unused-parameter -Wno-error=unused-variable -Wno-error=sign-compare")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
endif(MSVC)

find_package(OpenGL REQUIRED)

function(copy_dlls)
    set(DLLS 
        ${CMAKE_SOURCE_DIR}/glut/bin/freeglut.dll
    )

    file(COPY ${DLLS} DESTINATION ./Debug)
    file(COPY ${DLLS} DESTINATION ./Release)
    file(COPY ${DLLS} DESTINATION ./RelWithDebInfo)
endfunction()

add_subdirectory(GeometryLib)
add_subdirectory(Engine)
add_subdirectory(Starter)
