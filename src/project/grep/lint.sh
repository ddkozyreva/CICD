#!bin/bash
lint_output_grep=""
clang-format -n *.c > lint_output_grep
if [ -z "$lint_output_grep" ];
then 
    exit 1
else
    exit 0
fi