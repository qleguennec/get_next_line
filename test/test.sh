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

function buff_size {
	sed -i'' -s "s/define BUFF_SIZE.*/define BUFF_SIZE\t\t$1/" get_next_line.h
}

for SIZE in ${SIZES[@]}; do
	buff_size $SIZE
	make re > /dev/null
	echo -en "Testing for BUFF_SIZE\t$SIZE\t"
	MY=$(./gnl-test cat get_next_line.c)
	CAT=$(cat get_next_line.c)
	if [ ! "$MY" = "$CAT" ]; then
		echo "$MY"
		echo -e "$RED"WRONG FOR SIZE $SIZE$END
		exit 1
	else
		echo -e "$GREEN"OK$END
	fi
done

echo "GET_NEXT_LINE_PATH = $PWD" > test/config.ini
cd test

if [ ! -d "moulitest" ]; then
	git clone https://github.com/yyang42/moulitest.git
fi

mv config.ini moulitest
make -C moulitest gnl > result.log
RESULT=$(cat result.log | grep ">>>>" | grep spec | grep -v "Ok !")
if [ -z "$RESULT" ]; then
	echo -e "$GREEN"MOULITEST OK$END
	exit 0
else
	echo -e "$RED"MOULITEST NOK$END
	echo $RESULT
	exit 1
fi
