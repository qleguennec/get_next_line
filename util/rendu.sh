#!/bin/bash

GITHUB_URL=$(git remote -v | grep push | awk '{print $2}')
PROJECT_NAME=$(echo $GITHUB_URL | awk -F/ '{print $NF}' | cut -d. -f1)
if [ -x $PROJECT_DIR ]; then
	PROJECT_DIR=/tmp/$PROJECT_NAME
fi
RENDU_URL=$1

echo NAME: $PROJECT_NAME
echo DIR: $PROJECT_DIR

OLDDIR=$PWD

if [ -n "$RENDU_URL" ]; then
	git clone $42_URL /tmp
else
	if [ -d "$PROJECT_DIR" ]; then
		rm -rf $PROJECT_DIR
	fi
	mkdir $PROJECT_DIR
fi

CPY=(src/get_next_line.c includes/get_next_line.h auteur Makefile)

for DIR in ${CPY[@]}; do
	cp -r $DIR $PROJECT_DIR
done

cd $PROJECT_DIR
LIBDIR=. make deps
sed -i'' -s 's/<get_next_line.h>/"get_next_line.h"/g' get_next_line.c
rm Makefile
ls -la

exit 0
