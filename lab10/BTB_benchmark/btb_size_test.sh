#!/bin/bash

branch_count=1

while [ $branch_count -le 16384 ]
do
  echo ""
  echo "Branches count: $branch_count"
  make count_branches=$branch_count offset=8 > /dev/null
  sudo bin/BTB_benchmark
  branch_count=$(( branch_count * 2 ))
done