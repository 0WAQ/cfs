
project(test)

# 宏
macro(ADDTEST FILENAME)
    # 编译test_rbtree, 并链接库, 添加编译依赖, test依赖于cfs
    add_executable(${FILENAME} ${FILENAME}.c)
    target_link_libraries(${FILENAME} PRIVATE cfs)
    add_dependencies(${FILENAME} cfs)
endmacro(ADDTEST)


ADDTEST(${PROJECT_NAME}_rbtree)

