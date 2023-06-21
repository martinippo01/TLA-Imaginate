#! /bin/bash

set -e
ROOT="$(dirname "$0")"

echo "Relocating script to '$ROOT'..."
cd "$ROOT/.."

if [ $# -eq 2 ]; then
    cat "$1" | ./bin/Compiler $2
elif [ $# -eq 1 ]; then
    cat "$1" | ./bin/Compiler
else
    echo "Cantidad de argumentos invalidos. arg1: <program_path> arg2(opcional): -x"
fi

