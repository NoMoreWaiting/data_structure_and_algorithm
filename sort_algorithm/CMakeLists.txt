#1.cmake verson, 指定cmake版本 
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(platform x64)

#2.project name, 指定项目的名称, 一般和项目的文件夹名称对应
PROJECT(Algorithm)

#3.head file path, 头文件目录
INCLUDE_DIRECTORIES(
./include # for common head file
./SortAlgorithm
)

#4.source directory, 源文件目录
AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./include DIR_SRCS)
AUX_SOURCE_DIRECTORY(./SortAlgorithm DIR_SRCS)

#5.set environment variable, 设置环境变量, 编译用到的源文件全部都要放到这里, 否则编译能够通过, 但是执行的时候会出现各种问题, 比如"symbol lookup error xxxxx , undefined symbol"
SET(TEST_MATH
${DIR_SRCS}
)

#6.add executable file, 添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})

#7.add link library, 添加可执行文件所需要的库, 比如我们用到了libm.so（命名规则：lib+name+.so）, 就添加该库的名称
# 这里暂时没有用到
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} mysql) 
