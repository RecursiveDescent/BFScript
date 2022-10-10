cmake_minimum_required(VERSION 3.10)

project(BFVM VERSION 1.0)

AUX_SOURCE_DIRECTORY(src DIR)

AUX_SOURCE_DIRECTORY(src/compiler DIR)

add_executable(main ${DIR})