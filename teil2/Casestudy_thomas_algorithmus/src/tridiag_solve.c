#include "tridiag_solve.h"

void thomas(double* sol, double* a, double* b, double* c, double* rhs, int n){
	// Initialisierung
	double tmp;
	c[0] /= b[0];
	rhs[0] /= b[0];

	// Vorwärtsschleife
	for (int i = 0; i < n-2; i++){
		tmp = 1.0 / (b[i+1] - a[i] * c[i]);
		c[i+1] *= tmp;
		rhs[i+1] = (rhs[i+1] - a[i] * rhs[i]) * tmp;
	}
	// Letzter Schritt
	rhs[n-1] = (rhs[n-1] - a[n-2] * rhs[n-2]) / (b[n-1] - a[n-2] * c[n-2]);

	// Rückwärtssubstitution
	sol[n-1] = rhs[n-1];
	for (int i = n-2; i > -1; i--){
		sol[i] = rhs[i] - c[i] * sol[i+1];
	}
}
