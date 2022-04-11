#!/bin/env python3

import sys
import os
import subprocess
from dotenv import load_dotenv

def usage():
    print("Usage:")
    print("    test.py <test folder>")

def main():
    load_dotenv()
    BIN = os.getenv("BINF")
    if BIN == None:
        print("ERROR: Enviroment variable BINF is not provided in the .env file", file=sys.stderr)
        exit(1)
    if len(sys.argv) < 2:
        usage()
        print("ERROR: No argument provided", file=sys.stderr)
        exit(1)
    if not os.path.isdir(sys.argv[1]):
        print("ERROR: The provided folder does not exists or is a file", file=sys.stderr)
        exit(1)

    stmbin = os.path.join(str(BIN), "stm")
    for curf, folders, files in os.walk(sys.argv[1]):
        for f in files:
            curp = os.path.join(curf, f)
            try:
                subprocess.call([stmbin, "-f", curp])
            except FileNotFoundError:
                print("ERROR: Could not find the STM executable", file=sys.stderr)
                exit(1)


if __name__ == "__main__":
    main()
