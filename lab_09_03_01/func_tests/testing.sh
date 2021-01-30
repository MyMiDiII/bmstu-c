#!/bin/bash

num_pos=6
num_neg=9

ext=".txt"

out_ext="_out$ext"
args_ext="_args$ext"
res_ext="_res$ext"
err_ext="_err$ext"

dir="func_tests/"
pos="pos_"
neg="neg_"

check_test()
{
    echo -en "\e[1;36mTEST $2\e[0m    "
    prefix="$dir$1$2/$1$2"

    out="$prefix$out_ext"
    args_file="$prefix$args_ext"
    args=`fmt $args_file`
    errs_file="$prefix$err_ext"
    errs=`fmt $errs_file`

    res="$prefix$res_ext"

    ./app.exe $args > $res

    if ( [ $? == $errs ] && (cmp -s $out $res) )
    then
        echo -e "\e[32mPASSED\e[0m"
        rm -f $res
    else
        echo -e "\e[31mFAILED\e[0m"
    fi
}

memory_check_test()
{
    echo -en "\e[1;36mTEST $2\e[0m    "
    prefix="$dir$1$2/$1$2"

    out="$prefix$out_ext"
    args_file="$prefix$args_ext"
    args=`fmt $args_file`

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./app.exe $args
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

echo -e "\e[1;33mMEMORY TESTING\e[0m"
echo

echo -e "\e[1;32mPOSITIVE TESTS\e[0m"

for i in $(seq -f "%02g" 1 $num_pos)
do
    memory_check_test $pos $i
done

echo
echo -e "\e[1;31mNEGATIVE TESTS\e[0m"

for i in $(seq -f "%02g" 1 $num_neg)
do
    memory_check_test $neg $i
done
