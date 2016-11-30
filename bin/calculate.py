#!/usr/bin/env python
# -*- coding: utf-8 -*-

from math import *
import argparse
import re

# Arguments handling
parser = argparse.ArgumentParser(description="Calcul une valeur pour un point")
parser.add_argument("point", type=str, help="Les coordonnees")
parser.add_argument("exp", type=str, help="Expression a calculer (x1;x2;...)")
args = parser.parse_args()

def calc(vals):
    nexp = re.sub("x(\d+)", r"vals[\1-1]", args.exp)
    return eval(nexp)

if __name__ == "__main__":
        vals = [float(c) for c in args.point.split()]
        print calc(vals)
    

