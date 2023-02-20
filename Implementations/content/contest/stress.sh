# Usage: 'sh stress.sh'
# A_gen takes in i as a seed in stdin
for((i = 1; ; ++i)); do
    echo $i
    echo $i > Agenin
    ./A_gen < Agenin > int
    ./A < int > Aout
    ./A_naive < int > Anaiveout
    diff -w Aout Anaiveout || break
done