#!/bin/sh
export LANG=en_US.UTF-8

echo "cleaning the history build files ..."

rm -rf build

echo "delete successfully."
mkdir build

echo "start to build ..."
cd build

cmake ..

make

echo "build successfully."

./cjson_test
