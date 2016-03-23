#!/bin/bash

RM=(.git .gitignore lib test util .travis.yml)

for DIR in ${RM[@]}; do
	rm -rf $DIR 2> /dev/null
done
