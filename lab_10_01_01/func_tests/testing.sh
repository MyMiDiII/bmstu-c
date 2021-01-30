#!/bin/bash

num_pos=2
num_neg=6

ext=".txt"

out1_ext="_out1$ext"
out2_ext="_out2$ext"
args_ext="_args$ext"
res1_ext="_res1$ext"
res2_ext="_res2$ext"
err_ext="_err$ext"

dir="func_tests/"
pos="pos_"
neg="neg_"

check_test()
{
    echo -en "\e[1;36mTEST $2\e[0m    "
    prefix="$dir$1$2/$1$2"

    out1="$prefix$out1_ext"
    out2="$prefix$out2_ext"
    args_file="$prefix$args_ext"
    args=`fmt $args_file`
    errs_file="$prefix$err_ext"
    errs=`fmt $errs_file`

    res1="$prefix$res1_ext"
    res2="$prefix$res2_ext"

    ./app.exe $args

    if ( [ $? == $errs ] && ( [ $1 = $neg ] || ( (cmp -s $out1 $res1) && (cmp -s $out2 $res2) ) ) ) 
    then
        echo -e "\e[32mPASSED\e[0m"
        rm -f $res1 $res2
    else
        echo -e "\e[31mFAILED\e[0m"
    fi
}

memory_check_test()
{
    echo -e "\e[1;36mTEST $2\e[0m    "
    prefix="$dir$1$2/$1$2"

    out="$prefix$out_ext"
    args_file="$prefix$args_ext"
    args=`fmt $args_file`

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./app.exe $args
}

echo
echo -e "\e[1;33mFUNCTIONAL TESTING\e[0m"

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

echo
echo -e "\e[1;33mMEMORY TESTING\e[0m"

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
