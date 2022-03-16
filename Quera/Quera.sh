#!/bin/bash

mkdir ./$1
mkdir ./$1/in ./$1/out

for (( c=1; c<=$2; c++))
do
    touch ./$1/in/input$c.txt
    touch ./$1/out/output$c.txt
done

if [ -n "$3" ];then
    if [ $3 == "-c" ];then
        touch ./$1/tester.cpp
    fi
fi

#touch ./$1/Compress.sh

echo '#!/bin/bash

if [ -n "$1" ];then
    if [ $1 == "-c" ];then
        zip -r problem.zip ./in ./out
    elif [ $1 == "-h" ];then
        echo "nothing to compress in & out folder"
        echo "-c for compress tester.cpp too"
        echo "-h : for help"
    else
        echo "Wrong input!"
        echo "-h : for help"
    fi
else
    zip -r problem.zip ./in ./out
fi' > ./$1/Compress.sh

chmod +x ./$1/Compress.sh
