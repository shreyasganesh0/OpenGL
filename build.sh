#!/bin/zsh
# Print debug info

rm -rf build

mkdir -p build

export PKG_CONFIG_PATH=$(pwd)/pkgconfig:$PKG_CONFIG_PATH;

gcc src/main.cpp -o build/myapp $(pkg-config --cflags --libs glfw3) -framework OpenGL;
