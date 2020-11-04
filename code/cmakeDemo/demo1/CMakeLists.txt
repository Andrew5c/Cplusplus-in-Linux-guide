cmake_minimum_required(VERSION 2.8)

project(DEMO1)

# 搜索源文件
aux_source_directory(. SRCS)

# 添加子目录
# 此时它会进入该子目录搜索txt文件并执行
add_subdirectory(sort)


# 生成指定目标文件
add_executable(demo main.cpp)

# 添加链接库
target_link_libraries(demo sort1)
