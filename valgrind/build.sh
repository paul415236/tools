#!/bin/bash

PWD=$(pwd)

mkdir -p ${PWD}/release
RELEASE=${PWD}/release

cd valgrind-3.13.0

echo "prefix: ${RELEASE}"

./configure --host=arm-none-linux-gnueabi \
	--prefix=${RELEASE} \
	CFLAGS=-static

make
sudo make install
