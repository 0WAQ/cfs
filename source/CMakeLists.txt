
project(cfs)

# 获取文件列表
file(GLOB_RECURSE C_LIST "*.c" "*.h")

# 构建静态库
add_library(${PROJECT_NAME} STATIC ${C_LIST})

# 设置静态库的搜索路径, 属性PUBLIC, 传播给所有使用该库的项目
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_SOURCE_DIR}/../include
)
