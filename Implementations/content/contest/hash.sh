#!/bin/bash
# Modern replacement for KACTL hash.sh
# Usage: bash hash.sh < file.cpp

g++-13 -E -dD -P - <&0 2>/dev/null | tr -d '[:space:]' | md5sum | cut -c-6