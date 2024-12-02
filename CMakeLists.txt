cmake_minimum_required(VERSION 3.30)
project(CompilersProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompilersProject main.cpp
        src/LexicalAnalyser/LexicalAnalyser.cpp
        src/LexicalAnalyser/LexicalAnalyser.h
        src/Node/Node.cpp
        src/Node/Node.h
        src/NFA/NFA.cpp
        src/NFA/NFA.h
        src/DFA/DFA.cpp
        src/DFA/DFA.h
        src/Utils/utils.cpp
        src/Utils/utils.h
        src/NFA/NFA_builder.cpp
        src/NFA/NFA_builder.h)
