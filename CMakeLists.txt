cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(namegen_svc)

find_package(httplib COMPONENTS OpenSSL ZLIB Brotli)

configure_file(data/adjectives.txt adjectives.txt COPYONLY)
configure_file(data/animals.txt animals.txt COPYONLY)
configure_file(data/birds.txt birds.txt COPYONLY)

add_library(generators include/generator.hpp src/generator.cpp)
target_include_directories(generators PUBLIC "include")

add_executable(namegen_svc src/main.cpp)

target_link_libraries(namegen_svc httplib::httplib)
target_link_libraries(namegen_svc generators)
