#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

void multiplyMatrix(double** m1, double** m2, double** result, int n);
double** allocateMatrix(int n);
void freeMatrix(double** matrix, int n);

#endif