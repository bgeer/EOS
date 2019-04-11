#!/usr/bin/env bash
DIR=$1

for file in $DIR/*
do
	case $file in *.jpg )
		echo "file: "$file
		convert ${file%.*}.jpg -resize 128x128 ${file%.*}.png;;
esac
done
