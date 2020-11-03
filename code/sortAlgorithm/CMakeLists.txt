# cmake 最低版本要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (sortAlgorithm)

# 查找当前目录下的所有源文件
# 并保存到SRCS变量中
aux_source_directory (. SRCS)

# 引用上面的变量，指定生成的目标
add_executable (sort ${SRCS})
