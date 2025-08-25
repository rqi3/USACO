/**
 * Description: running tests. pc2submit E.cpp
 * Source: own
 */
import glob; import sys; import os

for input in glob.glob(f"samps/{sys.argv[1]}*/sample/*.in"):
    print("\nInput:")
    os.system(f"cat {input}")
    print("Output:")
    os.system(f"bash run.sh {sys.argv[1]} < {input}")
    print("Answer:")
    os.system(f"cat {input[:-3]}.ans")