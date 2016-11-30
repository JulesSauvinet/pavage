#!/usr/bin/env python
# -*- coding: utf-8 -*-

from math import sin, cos, tan
from random import uniform
import argparse
import re

# Arguments handling
parser = argparse.ArgumentParser(description="Genere des jeux de tests pour le pavage")
parser.add_argument("dimension", type=int, help="Nombre de dimension")
parser.add_argument("nb", type=int, help="Nombre de points a generer")
parser.add_argument("exp", type=str, help="Expression a calculer (x1;x2;...)")
args = parser.parse_args()

MINVAL = -210
MAXVAL = 210

def calc(vals):
    nexp = re.sub("x(\d+)", r"vals[\1-1]", args.exp)
    return eval(nexp)

if __name__ == "__main__":
    print("{}\n{}".format(args.dimension, args.nb))
    for i in range(args.nb):
        vals = [uniform(MINVAL, MAXVAL) for _ in range(args.dimension)]
        l = "{} {} ".format(" ".join({str(v) for v in vals}), calc(vals))
        print(l)
