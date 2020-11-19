#!/usr/bin/env python3

import numpy as np
from timeit import timeit
from scipy.linalg import solve, solve_banded
from cytridiag import cythomas

def solve_banded2(A, d):
	# AB-Matrix für banded_solve
	AB = np.zeros((3, A.shape[0]))
	AB[2,:-1] = A.diagonal(offset=-1)
	AB[1, :] = A.diagonal(offset=0)
	AB[0, 1::] = A.diagonal(offset=1)
	return solve_banded((1,1), AB, d)

if __name__ == '__main__':
	# Erzeuge Zufallsvektoren
	N = 10000
	a = np.random.random(N-1)
	b = np.random.random(N)
	c = np.random.random(N-1)
	rhs = np.random.random(N)
	# Erstelle die Tridiagonalmatrix
	T = np.diag(a, k=-1) + np.eye(N) * b + np.diag(c, k=+1)
	# Löse T*x = rhs mit scipy's solve
	t1 = timeit(lambda: solve(T, rhs), number = 1) / 1
	# Löse T*x = rhs mit scipy's banded_solve
	t2 = timeit(lambda: solve_banded2(T, rhs), number = 10) / 10
	# Löse es jetzt mit unserem cython-wrapper für die c-funktion:
	t3 = timeit(lambda: cythomas(T, rhs), number = 10) / 10
	print(f"N = {N}")
	print("------------------------------------")
	print(f"(1) scipy's solve:        {t1:E} s")
	print(f"(2) scipy's solve_banded: {t2:E} s ==> {int(t1/t2)}x schneller als (1)")
	print(f"(3) C-Wrapper Thomas-Alg: {t3:E} s ==> {int(t1/t3)}x schneller als (1)")



