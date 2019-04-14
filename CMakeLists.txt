# Minimum CMake version required to generate
# our build system
cmake_minimum_required(VERSION 3.0)

# Name of our Project
project(HX711)

add_executable(HX711 HX711.cpp HX711_main.cpp)

target_link_libraries(HX711 wiringPi)

