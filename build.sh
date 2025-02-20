#!/bin/zsh
# Print debug info

rm -rf build

mkdir -p build

gcc src/main.cpp -o build/myapp -Llibs -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -Wall -Iinclude;
