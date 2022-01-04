cmake_minimum_required(VERSION 3.15)
project(Ice_Examples VERSION 1.0
                     DESCRIPTION "my database"
                     LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
