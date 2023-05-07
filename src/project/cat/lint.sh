#!bin/bash
lint_output_cat=""
clang-format -n *.c > lint_output_cat
if [ -z "$lint_output_cat" ];
then 
    exit 1
else
    exit 0
fi