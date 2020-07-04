project(GeometryLib)

set(GeometryLib_SRCS
  Box.cpp
  Box.h
  Cube.cpp
  Cube.h
  EmptyPS.cpp
  EmptyPS.h
  Essential.cpp
  Essential.h
  GeometryLib.cpp
  GeometryLib.h
  Intersection.cpp
  Intersection.h
  Line.cpp
  Line.h
  Plane.cpp
  Plane.h
  PointSet.cpp
  PointSet.h
  Primitives.h
  Ray.cpp
  Ray.h
  RectangleAA.cpp
  RectangleAA.h
  Segment.cpp
  Segment.h
  SquareAA.cpp
  SquareAA.h
  Surface.cpp
  Surface.h
  Surfaces.h
  Triangle.cpp
  Triangle.h
  Vector.cpp
  Vector.h
  Vertex.cpp
  Vertex.h
  VolumetricObject.cpp
  VolumetricObject.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/ FILES ${GeometryLib_SRCS})

add_library(GeometryLib STATIC ${GeometryLib_SRCS})

target_include_directories(GeometryLib
	PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
