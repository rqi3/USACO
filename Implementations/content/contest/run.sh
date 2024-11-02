# Usage: sh run.sh L < L.in
# Using g++-13 for Egor's computer (hashmap + Tree<int>)
g++-13 -std=c++17 -O3 $1.cpp -o $1 && ./$1