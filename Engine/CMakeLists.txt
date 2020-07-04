project(Engine)

set(Engine_SRCS
  BoxPH.cpp
  BoxPH.h
  Camera.cpp
  Camera.h
  Color.cpp
  Color.h
  CubePH.cpp
  CubePH.h
  DrawEngine.cpp
  DrawEngine.h
  Engine.cpp
  Engine.h
  PhysicsObject.cpp
  PhysicsObject.h
  PhysicsObjects.h
  PhysicsProcessor.cpp
  PhysicsProcessor.h
  Player.cpp
  Player.h
  TextObject.cpp
  TextObject.h
  World.cpp
  World.h
  WorldChunk.cpp
  WorldChunk.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/ FILES ${Engine_SRCS})

add_library(Engine STATIC ${Engine_SRCS})

target_include_directories(Engine
	PUBLIC
  ${CMAKE_SOURCE_DIR}/glut/include
  ${OPENGL_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Engine
  GeometryLib
  ${CMAKE_SOURCE_DIR}/glut/lib/freeglut.lib
  ${OPENGL_LIBRARIES}
)
