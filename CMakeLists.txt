cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

project (
  "1c-admission"
  VERSION 1.0.0
  DESCRIPTION ""
)

set (
  SOURCES
  maybe.cpp
  error.cpp
  server.cpp
  storage.cpp
)

set (
  HEADERS
  maybe.hpp
  error.hpp
  server.hpp
  client.hpp
  storage.hpp
)

set (
  CLIENT_SOURCES
  client.cpp
  error.cpp
  maybe.cpp
)

find_package (Threads)

add_executable(server ${SOURCES} main.cpp)
add_executable(client ${CLIENT_SOURCES} client_main.cpp)
target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})