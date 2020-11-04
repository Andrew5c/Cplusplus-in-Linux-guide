# 查找源文件
aux_source_directory(. DIR_LIB_SRCS)

# 生成静态链接库
add_library(sort1 ${DIR_LIB_SRCS})
