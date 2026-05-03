cmake_minimum_required(VERSION 3.14)
project(Daily_Study)
# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成 compile_commands.json 供 clangd 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 将生成的执行文件放入build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 开启编译警告
add_compile_options(-Wall -Wextra)
# 添加子目录cmake文件
add_subdirectory(day24_ThreadPool)