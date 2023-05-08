#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE1="text.txt"
TEST_FILE2="text2"
TEST_FILE2="text2"
WORD="SUn"

echo /dev/null > log.txt
echo "Первый тест"

for var in -e -i -v -c -l -n #-v -E -T --number-nonblank --number --squeeze-blank
do
    TEST1="$var $WORD $TEST_FILE1"
    echo "$TEST1"
    ./s21_grep $TEST1 > s21_grep.txt
    grep $TEST1 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ];
    then
        COUNTER_SUCCESS=$(($COUNTER_SUCCESS+1))
    else
        echo "$TEST1" >> log.txt
        COUNTER_FAIL=$(($COUNTER_FAIL+1))
    fi
    rm s21_grep*.txt grep*.txt
done

for var in -e -i -v -c -l -n #-v -E -T --number-nonblank --number --squeeze-blank
do
    for test_file1 in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3
    do
        for test_file2 in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3
        do
            TEST1="$var $WORD $test_file1 $test_file2"
            echo "$TEST1"
            ./s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ];
            then
                COUNTER_SUCCESS=$(($COUNTER_SUCCESS+1))
            else
                echo "$TEST1" >> log.txt
                COUNTER_FAIL=$(($COUNTER_FAIL+1))
            fi
            rm s21_grep*.txt grep*.txt
        done
    done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

if [ $COUNTER_FAIL -ne 0 ];
then
  exit 1
else
  exit 0
fi