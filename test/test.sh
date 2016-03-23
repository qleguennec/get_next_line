#!/bin/bash

SIZES=(1 10 42 100 1000 10000)

BLACK="\033[0;30m"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"
WHITE="\033[0;37m"
END="\033[0m"

OK=$GREEN
NOK=$RED
INFO=$CYAN

function buff_size {
	sed -i'' -s "s/define BUFF_SIZE.*/define BUFF_SIZE $1/" get_next_line.h
}

OLDDIR=$PWD
make rendu
cp test/main.c /tmp/libgnl
cd /tmp/libgnl

echo -e "$INFO"Simple cat tests$END
for SIZE in ${SIZES[@]}; do
	buff_size $SIZE
	make -C libft/ fclean > /dev/null && make -C libft > /dev/null
	clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -o gnl-test main.o get_next_line.o -I libft/includes -L libft/ -lft
	echo -en "Testing for BUFF_SIZE\t$SIZE\t"
	MY=$(./gnl-test cat get_next_line.c)
	CAT=$(cat get_next_line.c)
	if [ ! "$MY" = "$CAT" ]; then
		echo "$MY"
		echo -e "$NOK"WRONG FOR SIZE $SIZE$END
		exit 1
	else
		echo -e "$OK"OK$END
	fi
done

cd $OLDDIR
make rendu

if [ ! -d "test/moulitest" ]; then
	echo -ne "$INFO""Fetching moulitest "$END
	git clone https://github.com/yyang42/moulitest.git test/moulitest --quiet
	if [ $? -ne 0 ]; then
		echo -e "$NOK"NOK$END
		exit 1
	else
		echo -e "$OK"OK$END
	fi
fi

echo -e "$INFO"Tesing with moulitest$END
echo "GET_NEXT_LINE_PATH = /tmp/libgnl" > test/moulitest/config.ini
cd test
make -C moulitest gnl > result.log 2>&1 || cat result.log

if [ $? -ne 0 ]; then
	exit 1
fi

RESULT=$(cat result.log | grep ">>>>" | grep "[FAIL]")
if [ -z "$RESULT" ]; then
	echo -e "$OK"MOULITEST OK$END
	exit 0
else
	echo -e "$NOK"MOULITEST NOK$END
	echo -e $RESULT
	exit 1
fi
