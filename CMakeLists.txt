cmake_minimum_required(VERSION 2.8)

project(q27)

include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
#if(COMPILER_SUPPORTS_MARCH_NATIVE)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
#endif()

set(${PROJECT_NAME}_SOURCES
  src/cpp/action.h
  src/cpp/Board.hpp
  src/cpp/filewriter.cpp
  src/cpp/filewriter.h
  src/cpp/Symmetry.cpp
  src/cpp/Symmetry.hpp
  )

add_library(${PROJECT_NAME}_static
  STATIC
  ${${PROJECT_NAME}_SOURCES}
  )
target_link_libraries(${PROJECT_NAME}_static
  ${ALL_LIBRARIES})

add_executable(${PROJECT_NAME} "src/cpp/coronal2.cpp")

target_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}_static
  ${ALL_LIBRARIES})
