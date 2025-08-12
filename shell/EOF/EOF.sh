#!/bin/bash

VAR="Hello, World!"
# 使用 Here Document 创建一个新文件
cat << EOF > EOFSample.txt
  This is the first line.
  $VAR
EOF
# 查看文件内容
cat EOFSample.txt

cat << 'EOF' > EOFSample.txt
  This is the first line.
  $VAR
EOF
# 查看文件内容
cat EOFSample.txt



