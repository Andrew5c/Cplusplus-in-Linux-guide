cmake_minimum_required(VERSION 2.8)

project(binaryTree-2)

# 搜索源文件
aux_source_directory(. SRCS)

# 生成指定目标文件
add_executable(demo main.cpp)
