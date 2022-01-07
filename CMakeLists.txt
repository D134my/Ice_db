cmake_minimum_required(VERSION 3.5)

project(IceDB  VERSION 1.2 
			   DESCRIPTION "IceDB -> simple database for unix like systems "
				LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)
include_directories(include)
include_directories(src)


add_executable(IceDB main.cpp ./src/ice_db.cpp ./src/argxx.cpp ./include/ice_db.hpp ./include/argxx.hpp)
target_link_libraries(IceDB stdc++fs)
install(TARGETS IceDB DESTINATION /usr/bin)
