#!/bin/bash

num_pos=5
num_neg=18

ext=".txt"

out_ext="_out$ext"
args_ext="_args$ext"
res_ext="_res$ext"
std_ext="_std$ext"
err_ext="_err$ext"

dir="func_tests/"
pos="pos_"
neg="neg_"

check_test()
{
    echo -en "\e[1;36mTEST $2\e[0m    "
    prefix="$dir$1$2/$1$2"

    out="$prefix$out_ext"
    std="$prefix$std_ext"
    args_file="$prefix$args_ext"
    args=`fmt $args_file`

    res="$prefix$res_ext"
    err="$prefix$err_ext"

    ./app.exe $args > $err 2>&1

    if ( (cmp -s $out $res) || [ $1 = $neg ] ) && (cmp -s $std $err)
    then
        echo -e "\e[32mPASSED\e[0m"
        rm -f $res $err
    else
        echo -e "\e[31mFAILED\e[0m"
    fi
}

echo -e "\e[1;33mFUNCTIONAL TESTING\e[0m"
echo

echo -e "\e[1;32mPOSITIVE TESTS\e[0m"

for i in $(seq -f "%02g" 1 $num_pos)
do
    check_test $pos $i
done

echo
echo -e "\e[1;31mNEGATIVE TESTS\e[0m"

for i in $(seq -f "%02g" 1 $num_neg)
do
    check_test $neg $i
done