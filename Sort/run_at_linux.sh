#! /bin/bash

# 编译
make

# 可执行程序寻找到动态库路径
cur_dir=`pwd`
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${cur_dir}

# 执行
./sort
