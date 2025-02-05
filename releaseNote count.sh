#!/bin/bash

# 检查参数数量
if [ "$#" -ne 2 ]; then
    echo "用法: $0 <第一个目录的行数> <第二个目录的行数>"
    exit 1
fi

# 获取需要读取的行数
COUNT1=$1
COUNT2=$2

# 第一个目录处理
cd /media/lxy/work/l3/map-engine-daemon || { echo "目录不存在: /media/lxy/work/l3/map-engine-daemon"; exit 1; }
BRANCH1=$(git rev-parse --abbrev-ref HEAD) # 获取第一个目录的git分支名
git log --oneline | head -n "$COUNT1" | /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote $COUNT1 1 0
if [ $? -ne 0 ]; then
    echo "在第一个目录中执行 releaseNote 失败"
    exit 1
fi

# 第二个目录处理
cd /media/lxy/work/l3/mapauto-engine || { echo "目录不存在: /media/lxy/work/l3/mapauto-engine"; exit 1; }
BRANCH2=$(git rev-parse --abbrev-ref HEAD) # 获取第二个目录的git分支名
git log --oneline | head -n "$COUNT2" | /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote $COUNT2 2 $COUNT1
if [ $? -ne 0 ]; then
    echo "在第二个目录中执行 releaseNote 失败"
    exit 1
fi

cat /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote.txt
echo ""
echo "English:"
echo "map-engine-daemon branch:$BRANCH1" # 输出第一个目录的git分支
echo "mapauto-engine branch:$BRANCH2" # 输出第二个目录的git分支

# 编译指令
# g++ -o releaseNote releaseNote.cpp