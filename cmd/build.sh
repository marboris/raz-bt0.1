#!/bin/bash
set -eu

CXX="c++"
CXXFLAGS=( -std=c++20 -O3 -pipe -static -Wall -pthread )

ROOT_DIR="${1:-.}"

find "$ROOT_DIR" -type f \( -iname "main.cpp" -o -iname "main.cc" \) | while IFS= read -r src; do
  dir="$(dirname "$src")"
  
  if ! cd "$dir"; then
    echo "Cannot enter directory: $dir" >&2
    continue
  fi
  
  if ! mkdir -p "bin"; then
    echo "Failed to create bin directory in: $dir" >&2
    continue
  fi

  base="$(basename "$src")"
  name="${base%.*}"
  outfile="bin/$name"

  echo "Building in $dir: $base -> $outfile"
  
  if "$CXX" "${CXXFLAGS[@]}" "$base" -o "$outfile"; then
    echo "Successfully built: $outfile"
  else
    echo "Build failed for: $base" >&2
  fi
  
  cd - > /dev/null
done
