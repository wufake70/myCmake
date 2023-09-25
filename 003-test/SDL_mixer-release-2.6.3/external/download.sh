#!/bin/sh

set -e

cd "$(dirname "$0")/.."
cat .gitmodules |
while IFS= read -r line; do
  if echo "$line" | grep -q '\[submodule'; then
    read -r path_line
    read -r url_line
    read -r branch_line
    path=$(echo "$path_line" | awk '{print $3}')
    url=$(echo "$url_line" | awk '{print $3}')
    branch=$(echo "$branch_line" | awk '{print $3}')
    
    # 检查目标路径是否已存在，如果存在则跳过下载
    if [ -d "$path" ]; then
      echo "submoudle existed：$path"
    else
      git clone "$url" "$path" -b "$branch" --recursive
    fi
  fi
done