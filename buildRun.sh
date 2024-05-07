#!/bin/bash
rm -r build
cmake -B build/
cmake --build build/
WAYLAND_DISPLAY=wayland-99 build/mirComp
