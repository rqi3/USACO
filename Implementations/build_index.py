import sys
import re

path = sys.argv[1]
with open(path) as f:
    lines = f.readlines()

def extract(s):
    tokens = s.strip().split()
    pn = int(tokens[-1])
    term = ' '.join(tokens[:-1])
    if '.' in term:
        start_pos = term.rfind('/') + 1
        end_pos = term.rfind('.')
        term = term[start_pos:end_pos].split()[0]
    return (term, pn)

dct = {}
for term, pn in [extract(s) for s in lines]:
    dct[term] = pn

res = []
for term, pn in sorted(dct.items()):
    res += term + " \\textbf{" + str(pn) + "} " + "\hskip 2ex "
print(''.join(res))

