#!/bin/bash

GITHUB_URL=$(git remote -v | grep push | awk '{print $2}')
PROJECT_NAME=$(echo $GITHUB_URL | awk -F/ '{print $NF}' | cut -d. -f1)
if [ -x $PROJECT_DIR ]; then
	PROJECT_DIR=/tmp/$PROJECT_NAME
fi
RENDU_URL=$1

echo NAME: $PROJECT_NAME
echo DIR: $PROJECT_DIR

if [ -n "$RENDU_URL" ]; then
	git clone $42_URL /tmp
else
	if [ -d "$PROJECT_DIR" ]; then
		rm -rf $PROJECT_DIR
	fi
	mkdir $PROJECT_DIR
fi

CPY=(get_next_line.* Makefile main.c)

for DIR in ${CPY[@]}; do
	cp -r $DIR $PROJECT_DIR
done

make -C $PROJECT_DIR all fclean

RM=(Makefile main.c)

for DIR in ${RM[@]}; do
	rm $PROJECT_DIR/$DIR
done

find $PROJECT_DIR -mindepth 2 -type d -name ".git" -exec rm -rf {} \; 2>/dev/null

ls -la $PROJECT_DIR

exit 0
