
project(tests)

# 生成可执行文件
add_executable(${PROJECT_NAME} test.c)

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE cfs)
