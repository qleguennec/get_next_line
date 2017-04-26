#! /bin/bash

if [ -z "$BRANCH" ]; then
	BRANCH="dev"
fi

if [ -z "$PORT" ]; then
	PORT="4242"
fi

RTDIR="rt-$BRANCH"
CLDIR="cl"
INCDIR="include"
GIT="http://github.com/lgatibel/42_rt.git"

if [ -d "$RTDIR/.git" ]; then
	cd "$RTDIR"
	git pull
	cd ..
else
	git clone -b "$BRANCH" "$GIT" "$RTDIR"
fi

if [ -d "$CLDIR" ]; then
	rm -rf "$CLDIR"
	mkdir "$CLDIR"
else
	mkdir "$CLDIR"
fi

if [ -d "$INCDIR" ]; then
	rm -rf "$INCDIR"
	mkdir "$INCDIR"
else
	mkdir "$INCDIR"
fi

echo Copying all cl files from "$RTDIR" to "$CLDIR"
find "$RTDIR/sources/cl" -print -exec cp {} "$CLDIR" \;
echo OK
