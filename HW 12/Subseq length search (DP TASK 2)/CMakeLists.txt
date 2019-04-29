cmake_minimum_required(VERSION 3.0)

project(DP_2_MAIN) # Вместо "MAIN" подставьте любое название файла
set(CMAKE_CXX_STANDARD 11) # Мы же на C++ 11 работаем вроде?
set(SOURCE_FILES subseq_template_length.cpp)
add_executable(MAIN ${SOURCE_FILES})