cmake_minimum_required(VERSION 3.5)

project(db LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(db main.cpp ice_db.cpp ice_db.h argxx.cpp argxx.h)
target_link_libraries(db stdc++fs)
