cmake_minimum_required(VERSION 3.20)
project(EmitterDev CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(emitter_dev
    
    "C++ Emitter (clang)/Emitter.cpp" "C++ Emitter (clang)/VariableDeclaration.cpp"   "C++ Emitter (clang)/TacToCpp.h"  )

target_include_directories(emitter_dev PRIVATE "C++ Emitter (clang)")