#!/bin/bash
# Check dependencies
echo "build.sh: Checking dependencies..."

for d in "libmiral-dev" "mir-graphics-drivers-desktop" "build-essential" "cmake" "pkg-config" "weston" "qtwayland5"
do
	if dpkg -l $d > /dev/null; then
		echo "build.sh: $d detected"
	else
		echo "build.sh: $d missing! Installing..."
		sudo apt install $d
	fi
done

echo "build.sh: Dependencies installed. Building..."
# Build mcomp
rm -r build
cmake -B build/
cmake --build build/
