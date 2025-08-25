# Usage: bash run.sh L < L.in
g++-13 -std=c++17 -O3 $1.cpp -o $1 && ./$1