#!/bin/bash

# 第一个目录处理
cd /media/lxy/work/l3/map-engine-daemon || { echo "目录不存在: /media/lxy/work/l3/map-engine-daemon"; exit 1; }
BRANCH1=$(git rev-parse --abbrev-ref HEAD)
# 获取最近标签对应的提交时间并+1秒（使用committer date）
TAG_COMMIT1=$(git describe --tags --abbrev=0)
TAG_TIME1=$(git log -1 --format=%ct "$TAG_COMMIT1")
((TAG_TIME1++))  # 排除标签提交
# 获取该时间之后的日志并计数
LOG1=$(git log --since=@$TAG_TIME1 --oneline)
COUNT1=$(echo "$LOG1" | grep -cE '^[0-9a-f]') 
# 添加空日志检测
if [ "$COUNT1" -eq 0 ]; then
    echo "警告：第一个仓库没有新提交"
fi

echo "$LOG1" | /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote $COUNT1 1 0
if [ $? -ne 0 ]; then
    echo "在第一个目录中执行 releaseNote 失败"
    exit 1
fi

# 第二个目录处理
cd /media/lxy/work/l3/mapauto-engine || { echo "目录不存在: /media/lxy/work/l3/mapauto-engine"; exit 1; }
BRANCH2=$(git rev-parse --abbrev-ref HEAD)
# 获取最近标签对应的提交时间并+1秒（使用committer date）
TAG_COMMIT2=$(git describe --tags --abbrev=0)
TAG_TIME2=$(git log -1 --format=%ct "$TAG_COMMIT2")
((TAG_TIME2++))  # 排除标签提交
# 获取该时间之后的日志并计数
LOG2=$(git log --since=@$TAG_TIME2 --oneline)
COUNT2=$(echo "$LOG2" | grep -cE '^[0-9a-f]')
if [ "$COUNT2" -eq 0 ]; then
    echo "警告：第二个仓库没有新提交" 
fi

# 保留LOG1文件内容与LOG2对比，将去重后的LOG2和COUNT2传递给releaseNote
echo "$LOG1" | awk '{sub(/[^ ]+ /, ""); print}' > /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/log1_ccnc
LOG2_FILTERED=$(echo "$LOG2" | awk '{line=$0; sub(/[^ ]+ /, ""); if(!seen[$0]++) print line}' | 
awk 'BEGIN {while(getline <"/media/lxy/work/ccncResource/pcsh/releaseNoteAuto/log1_ccnc") seen[$0]++} {msg=$0; sub(/[^ ]+ /, ""); if(!seen[$0]++) print msg}' -)
COUNT2_FILTERED=$(echo "$LOG2_FILTERED" | grep -cE '^[0-9a-f]')

echo "$LOG2_FILTERED" | /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote $COUNT2_FILTERED 2 $COUNT1

if [ $? -ne 0 ]; then
    echo "在第二个目录中执行 releaseNote 失败"
    exit 1
fi

cat /media/lxy/work/ccncResource/pcsh/releaseNoteAuto/releaseNote.txt
echo ""
echo "English:"
echo "map-engine-daemon branch:$BRANCH1" # 输出第一个目录的git分支
echo "mapauto-engine branch:$BRANCH2" # 输出第二个目录的git分支

# 编译指令:g++ -o releaseNote releaseNote.cpp