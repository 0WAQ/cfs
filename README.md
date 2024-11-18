## 如何开始
- 建议使用vscode打开, 可以直接开始调试

## 目录结构

```
|--.vscode/
|  |--launch.json   # gdb调试相关配置
|  |--tasks.json    # 项目生产相关配置
|
|--include/
|  |--common/       # 通用
|  |--tools/        # 链表与红黑树
|  |--cfs_t.h
|  |--cfs.h
|  |--task_t.h
|  |--task.h
|
|--script/
|  |--build.sh      # 构建并生成项目
|  |--run.sh        # 运行测试文件
|
|--source/
|  |--tools/
|  |--cfs.c
|  |--task.c
|  |--CMakeLists.txt
|
|--tests/
|  |--CMakeLists.txt
|  |--test.c
|
|--.gitignore
|
|--CMakeLists.txt
|
|--README.md
```