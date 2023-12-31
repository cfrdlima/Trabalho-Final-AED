#include <stdio.h>
#include <stdlib.h>

typedef struct matrix Matrix;

// create node
Matrix *createNode(int row, int col, float value);
// create Matrix
Matrix *matrix_create(void);
// destroy Matrix
void matrix_destroy(Matrix *m);
// print Matrix
void matrix_print(Matrix *m);
// add Matrix
Matrix *matrix_add(Matrix *m, Matrix *n);
// multiply Matrix
Matrix *matrix_multiply(Matrix *m, Matrix *n);
// transpose Matrix
Matrix *matrix_transpose(Matrix *m);
// getElem Matrix
float matrix_getelem(Matrix *m, int x, int y);
// setElem Matrix
void matrix_setelem(Matrix *m, int x, int y, float elem);
