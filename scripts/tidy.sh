#!/bin/bash
cd $(dirname $0)/..

clang-tidy --config-file=.clang-tidy -p=./build/compile_commands.json ./nile/**/*.cpp ./nile/**/*.hpp 