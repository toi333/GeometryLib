project(Starter)

set(Starter_SRCS
  Starter.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/ FILES ${Starter_SRCS})

add_executable(Starter ${Starter_SRCS} ${shgroup})

target_link_libraries(Starter
  Engine
)

copy_dlls()
