#!/usr/bin/env python3

import numpy as np
from BinSudoku import c_solve, Sudoku

if __name__ == '__main__':
    S = np.loadtxt("backtracking_hard.txt", dtype=np.int32)
    print(c_solve(S))

    # Lösung 2: RAII:
    sud = Sudoku(S)
    print(sud.solve())