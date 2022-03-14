#!/usr/bin/python

import os
import sys

def main():
    TOOLS_PATH = os.path.abspath(sys.path[0])
    CLANG_FORMAT = os.path.join(TOOLS_PATH, "clang-format")

    if (len(sys.argv) < 2):
        print("Usage: ./formatfix.py file [file ...]")
        sys.exit(1)

    for arg in sys.argv[1:]:
        if os.path.isfile(arg):
            cmd = CLANG_FORMAT + " -i " + arg
            os.system(cmd)
        else:
            print("Unknown file name " + arg)

if __name__ == '__main__':
    main()
