# Usage: sh run.sh L < L.in
# Using g++-12 for Egor's computer (hashmap + Tree<int>)
g++-12 -std=c++17 -O3 $1.cpp -o $1 && ./$1